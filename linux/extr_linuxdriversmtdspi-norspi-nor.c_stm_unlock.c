#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int u8 ;
struct mtd_info {scalar_t__ size; } ;
struct spi_nor {int flags; struct mtd_info mtd; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int SNOR_F_HAS_SR_TB ; 
 int SR_BP0 ; 
 int SR_BP1 ; 
 int SR_BP2 ; 
 int SR_SRWD ; 
 int SR_TB ; 
 int ffs (int) ; 
 int ilog2 (scalar_t__) ; 
 int order_base_2 (scalar_t__) ; 
 int read_sr (struct spi_nor*) ; 
 scalar_t__ stm_is_unlocked_sr (struct spi_nor*,scalar_t__,scalar_t__,int) ; 
 int write_sr_and_check (struct spi_nor*,int,int) ; 

__attribute__((used)) static int stm_unlock(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	struct mtd_info *mtd = &nor->mtd;
	int status_old, status_new;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;
	u8 shift = ffs(mask) - 1, pow, val;
	loff_t lock_len;
	bool can_be_top = true, can_be_bottom = nor->flags & SNOR_F_HAS_SR_TB;
	bool use_top;

	status_old = read_sr(nor);
	if (status_old < 0)
		return status_old;

	/* If nothing in our range is locked, we don't need to do anything */
	if (stm_is_unlocked_sr(nor, ofs, len, status_old))
		return 0;

	/* If anything below us is locked, we can't use 'top' protection */
	if (!stm_is_unlocked_sr(nor, 0, ofs, status_old))
		can_be_top = false;

	/* If anything above us is locked, we can't use 'bottom' protection */
	if (!stm_is_unlocked_sr(nor, ofs + len, mtd->size - (ofs + len),
				status_old))
		can_be_bottom = false;

	if (!can_be_bottom && !can_be_top)
		return -EINVAL;

	/* Prefer top, if both are valid */
	use_top = can_be_top;

	/* lock_len: length of region that should remain locked */
	if (use_top)
		lock_len = mtd->size - (ofs + len);
	else
		lock_len = ofs;

	/*
	 * Need largest pow such that:
	 *
	 *   1 / (2^pow) >= (len / size)
	 *
	 * so (assuming power-of-2 size) we do:
	 *
	 *   pow = floor(log2(size / len)) = log2(size) - ceil(log2(len))
	 */
	pow = ilog2(mtd->size) - order_base_2(lock_len);
	if (lock_len == 0) {
		val = 0; /* fully unlocked */
	} else {
		val = mask - (pow << shift);
		/* Some power-of-two sizes are not supported */
		if (val & ~mask)
			return -EINVAL;
	}

	status_new = (status_old & ~mask & ~SR_TB) | val;

	/* Don't protect status register if we're fully unlocked */
	if (lock_len == 0)
		status_new &= ~SR_SRWD;

	if (!use_top)
		status_new |= SR_TB;

	/* Don't bother if they're the same */
	if (status_new == status_old)
		return 0;

	/* Only modify protection if it will not lock other areas */
	if ((status_new & mask) > (status_old & mask))
		return -EINVAL;

	return write_sr_and_check(nor, status_new, mask);
}