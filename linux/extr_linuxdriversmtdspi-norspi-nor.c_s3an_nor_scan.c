#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int writebufsize; int size; int erasesize; } ;
struct spi_nor {int (* read_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ;int page_size; int /*<<< orphan*/  flags; TYPE_1__ mtd; int /*<<< orphan*/  read_opcode; int /*<<< orphan*/  program_opcode; int /*<<< orphan*/  erase_opcode; int /*<<< orphan*/  dev; } ;
struct flash_info {int n_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNOR_F_NO_OP_CHIP_ERASE ; 
 int /*<<< orphan*/  SNOR_F_S3AN_ADDR_DEFAULT ; 
 int /*<<< orphan*/  SPINOR_OP_READ ; 
 int /*<<< orphan*/  SPINOR_OP_XPP ; 
 int /*<<< orphan*/  SPINOR_OP_XRDSR ; 
 int /*<<< orphan*/  SPINOR_OP_XSE ; 
 int XSR_PAGESIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int s3an_nor_scan(const struct flash_info *info, struct spi_nor *nor)
{
	int ret;
	u8 val;

	ret = nor->read_reg(nor, SPINOR_OP_XRDSR, &val, 1);
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
	if (val & XSR_PAGESIZE) {
		/* Flash in Power of 2 mode */
		nor->page_size = (nor->page_size == 264) ? 256 : 512;
		nor->mtd.writebufsize = nor->page_size;
		nor->mtd.size = 8 * nor->page_size * info->n_sectors;
		nor->mtd.erasesize = 8 * nor->page_size;
	} else {
		/* Flash in Default addressing mode */
		nor->flags |= SNOR_F_S3AN_ADDR_DEFAULT;
	}

	return 0;
}