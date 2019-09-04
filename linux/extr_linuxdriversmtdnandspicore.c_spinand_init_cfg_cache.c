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
struct spinand_device {int /*<<< orphan*/ * cfg_cache; TYPE_3__* spimem; } ;
struct TYPE_4__ {unsigned int ntargets; } ;
struct nand_device {TYPE_1__ memorg; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* spi; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REG_CFG ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int spinand_read_reg_op (struct spinand_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spinand_select_target (struct spinand_device*,unsigned int) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 

__attribute__((used)) static int spinand_init_cfg_cache(struct spinand_device *spinand)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	struct device *dev = &spinand->spimem->spi->dev;
	unsigned int target;
	int ret;

	spinand->cfg_cache = devm_kcalloc(dev,
					  nand->memorg.ntargets,
					  sizeof(*spinand->cfg_cache),
					  GFP_KERNEL);
	if (!spinand->cfg_cache)
		return -ENOMEM;

	for (target = 0; target < nand->memorg.ntargets; target++) {
		ret = spinand_select_target(spinand, target);
		if (ret)
			return ret;

		/*
		 * We use spinand_read_reg_op() instead of spinand_get_cfg()
		 * here to bypass the config cache.
		 */
		ret = spinand_read_reg_op(spinand, REG_CFG,
					  &spinand->cfg_cache[target]);
		if (ret)
			return ret;
	}

	return 0;
}