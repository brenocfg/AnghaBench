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
struct TYPE_2__ {int size; } ;
struct spi_nor {int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_1__ mtd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPINOR_OP_CHIP_ERASE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,long long) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int erase_chip(struct spi_nor *nor)
{
	dev_dbg(nor->dev, " %lldKiB\n", (long long)(nor->mtd.size >> 10));

	return nor->write_reg(nor, SPINOR_OP_CHIP_ERASE, NULL, 0);
}