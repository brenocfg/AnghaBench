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
struct spinand_device {int dummy; } ;
struct TYPE_2__ {unsigned int ntargets; } ;
struct nand_device {TYPE_1__ memorg; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINBOND_CFG_BUF_READ ; 
 int /*<<< orphan*/  spinand_select_target (struct spinand_device*,unsigned int) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 
 int /*<<< orphan*/  spinand_upd_cfg (struct spinand_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int winbond_spinand_init(struct spinand_device *spinand)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int i;

	/*
	 * Make sure all dies are in buffer read mode and not continuous read
	 * mode.
	 */
	for (i = 0; i < nand->memorg.ntargets; i++) {
		spinand_select_target(spinand, i);
		spinand_upd_cfg(spinand, WINBOND_CFG_BUF_READ,
				WINBOND_CFG_BUF_READ);
	}

	return 0;
}