#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; } ;
struct spi_nor {int addr_width; int flags; int /*<<< orphan*/  dev; TYPE_1__ mtd; TYPE_2__* info; } ;
struct TYPE_4__ {int addr_width; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNOR_F_4B_OPCODES ; 
 int SNOR_F_HAS_4BAIT ; 
 int SPI_NOR_MAX_ADDR_WIDTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spi_nor_set_4byte_opcodes (struct spi_nor*) ; 

__attribute__((used)) static int spi_nor_set_addr_width(struct spi_nor *nor)
{
	if (nor->addr_width) {
		/* already configured from SFDP */
	} else if (nor->info->addr_width) {
		nor->addr_width = nor->info->addr_width;
	} else if (nor->mtd.size > 0x1000000) {
		/* enable 4-byte addressing if the device exceeds 16MiB */
		nor->addr_width = 4;
	} else {
		nor->addr_width = 3;
	}

	if (nor->addr_width > SPI_NOR_MAX_ADDR_WIDTH) {
		dev_err(nor->dev, "address width is too large: %u\n",
			nor->addr_width);
		return -EINVAL;
	}

	/* Set 4byte opcodes when possible. */
	if (nor->addr_width == 4 && nor->flags & SNOR_F_4B_OPCODES &&
	    !(nor->flags & SNOR_F_HAS_4BAIT))
		spi_nor_set_4byte_opcodes(nor);

	return 0;
}