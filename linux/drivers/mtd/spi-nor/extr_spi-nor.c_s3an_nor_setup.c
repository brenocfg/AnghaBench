#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_hwcaps {int dummy; } ;
struct TYPE_5__ {int writebufsize; int size; int erasesize; } ;
struct TYPE_4__ {int /*<<< orphan*/  convert_addr; } ;
struct spi_nor {int* bouncebuf; int page_size; TYPE_3__* info; TYPE_2__ mtd; TYPE_1__ params; int /*<<< orphan*/  flags; int /*<<< orphan*/  read_opcode; int /*<<< orphan*/  program_opcode; int /*<<< orphan*/  erase_opcode; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int n_sectors; int sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNOR_F_NO_OP_CHIP_ERASE ; 
 int /*<<< orphan*/  SPINOR_OP_READ ; 
 int /*<<< orphan*/  SPINOR_OP_XPP ; 
 int /*<<< orphan*/  SPINOR_OP_XSE ; 
 int XSR_PAGESIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  s3an_convert_addr ; 
 int spi_nor_xread_sr (struct spi_nor*,int*) ; 

__attribute__((used)) static int s3an_nor_setup(struct spi_nor *nor,
			  const struct spi_nor_hwcaps *hwcaps)
{
	int ret;

	ret = spi_nor_xread_sr(nor, nor->bouncebuf);
	if (ret < 0) {
		dev_err(nor->dev, "error %d reading XRDSR\n", (int) ret);
		return ret;
	}

	nor->erase_opcode = SPINOR_OP_XSE;
	nor->program_opcode = SPINOR_OP_XPP;
	nor->read_opcode = SPINOR_OP_READ;
	nor->flags |= SNOR_F_NO_OP_CHIP_ERASE;

	/*
	 * This flashes have a page size of 264 or 528 bytes (known as
	 * Default addressing mode). It can be changed to a more standard
	 * Power of two mode where the page size is 256/512. This comes
	 * with a price: there is 3% less of space, the data is corrupted
	 * and the page size cannot be changed back to default addressing
	 * mode.
	 *
	 * The current addressing mode can be read from the XRDSR register
	 * and should not be changed, because is a destructive operation.
	 */
	if (nor->bouncebuf[0] & XSR_PAGESIZE) {
		/* Flash in Power of 2 mode */
		nor->page_size = (nor->page_size == 264) ? 256 : 512;
		nor->mtd.writebufsize = nor->page_size;
		nor->mtd.size = 8 * nor->page_size * nor->info->n_sectors;
		nor->mtd.erasesize = 8 * nor->page_size;
	} else {
		/* Flash in Default addressing mode */
		nor->params.convert_addr = s3an_convert_addr;
		nor->mtd.erasesize = nor->info->sector_size;
	}

	return 0;
}