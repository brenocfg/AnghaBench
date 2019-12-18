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
typedef  scalar_t__ uint32_t ;
typedef  int u32 ;
struct spi_nor {int flags; int /*<<< orphan*/  dev; } ;
struct mtd_info {int erasesize; int size; } ;
struct erase_info {int addr; int len; } ;

/* Variables and functions */
 unsigned long CHIP_ERASE_2MB_READY_WAIT_JIFFIES ; 
 int EINVAL ; 
 int EIO ; 
 int SNOR_F_NO_OP_CHIP_ERASE ; 
 int /*<<< orphan*/  SPI_NOR_OPS_ERASE ; 
 int SZ_2M ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,long long,long long) ; 
 int /*<<< orphan*/  div_u64_rem (int,int,scalar_t__*) ; 
 scalar_t__ erase_chip (struct spi_nor*) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 struct spi_nor* mtd_to_spi_nor (struct mtd_info*) ; 
 int spi_nor_erase_multi_sectors (struct spi_nor*,int,int) ; 
 int spi_nor_erase_sector (struct spi_nor*,int) ; 
 scalar_t__ spi_nor_has_uniform_erase (struct spi_nor*) ; 
 int spi_nor_lock_and_prep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_unlock_and_unprep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int spi_nor_wait_till_ready (struct spi_nor*) ; 
 int spi_nor_wait_till_ready_with_timeout (struct spi_nor*,unsigned long) ; 
 int /*<<< orphan*/  write_disable (struct spi_nor*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static int spi_nor_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	u32 addr, len;
	uint32_t rem;
	int ret;

	dev_dbg(nor->dev, "at 0x%llx, len %lld\n", (long long)instr->addr,
			(long long)instr->len);

	if (spi_nor_has_uniform_erase(nor)) {
		div_u64_rem(instr->len, mtd->erasesize, &rem);
		if (rem)
			return -EINVAL;
	}

	addr = instr->addr;
	len = instr->len;

	ret = spi_nor_lock_and_prep(nor, SPI_NOR_OPS_ERASE);
	if (ret)
		return ret;

	/* whole-chip erase? */
	if (len == mtd->size && !(nor->flags & SNOR_F_NO_OP_CHIP_ERASE)) {
		unsigned long timeout;

		write_enable(nor);

		if (erase_chip(nor)) {
			ret = -EIO;
			goto erase_err;
		}

		/*
		 * Scale the timeout linearly with the size of the flash, with
		 * a minimum calibrated to an old 2MB flash. We could try to
		 * pull these from CFI/SFDP, but these values should be good
		 * enough for now.
		 */
		timeout = max(CHIP_ERASE_2MB_READY_WAIT_JIFFIES,
			      CHIP_ERASE_2MB_READY_WAIT_JIFFIES *
			      (unsigned long)(mtd->size / SZ_2M));
		ret = spi_nor_wait_till_ready_with_timeout(nor, timeout);
		if (ret)
			goto erase_err;

	/* REVISIT in some cases we could speed up erasing large regions
	 * by using SPINOR_OP_SE instead of SPINOR_OP_BE_4K.  We may have set up
	 * to use "small sector erase", but that's not always optimal.
	 */

	/* "sector"-at-a-time erase */
	} else if (spi_nor_has_uniform_erase(nor)) {
		while (len) {
			write_enable(nor);

			ret = spi_nor_erase_sector(nor, addr);
			if (ret)
				goto erase_err;

			addr += mtd->erasesize;
			len -= mtd->erasesize;

			ret = spi_nor_wait_till_ready(nor);
			if (ret)
				goto erase_err;
		}

	/* erase multiple sectors */
	} else {
		ret = spi_nor_erase_multi_sectors(nor, addr, len);
		if (ret)
			goto erase_err;
	}

	write_disable(nor);

erase_err:
	spi_nor_unlock_and_unprep(nor, SPI_NOR_OPS_ERASE);

	return ret;
}