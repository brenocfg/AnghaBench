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
typedef  int uint64_t ;
typedef  int u8 ;
struct mtd_info {int size; } ;
struct spi_nor {int flags; struct mtd_info mtd; } ;
typedef  int loff_t ;

/* Variables and functions */
 int SNOR_F_HAS_SR_TB ; 
 int SR_BP0 ; 
 int SR_BP1 ; 
 int SR_BP2 ; 
 int SR_TB ; 
 int ffs (int) ; 

__attribute__((used)) static void stm_get_locked_range(struct spi_nor *nor, u8 sr, loff_t *ofs,
				 uint64_t *len)
{
	struct mtd_info *mtd = &nor->mtd;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;
	int shift = ffs(mask) - 1;
	int pow;

	if (!(sr & mask)) {
		/* No protection */
		*ofs = 0;
		*len = 0;
	} else {
		pow = ((sr & mask) ^ mask) >> shift;
		*len = mtd->size >> pow;
		if (nor->flags & SNOR_F_HAS_SR_TB && sr & SR_TB)
			*ofs = 0;
		else
			*ofs = mtd->size - *len;
	}
}