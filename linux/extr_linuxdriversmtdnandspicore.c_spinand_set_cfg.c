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
typedef  scalar_t__ u8 ;
struct spinand_device {scalar_t__ cur_target; scalar_t__* cfg_cache; } ;
struct TYPE_2__ {scalar_t__ ntargets; } ;
struct nand_device {TYPE_1__ memorg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_CFG ; 
 scalar_t__ WARN_ON (int) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 
 int spinand_write_reg_op (struct spinand_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int spinand_set_cfg(struct spinand_device *spinand, u8 cfg)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	int ret;

	if (WARN_ON(spinand->cur_target < 0 ||
		    spinand->cur_target >= nand->memorg.ntargets))
		return -EINVAL;

	if (spinand->cfg_cache[spinand->cur_target] == cfg)
		return 0;

	ret = spinand_write_reg_op(spinand, REG_CFG, cfg);
	if (ret)
		return ret;

	spinand->cfg_cache[spinand->cur_target] = cfg;
	return 0;
}