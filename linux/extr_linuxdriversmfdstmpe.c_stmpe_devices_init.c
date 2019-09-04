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
struct stmpe_variant_info {int num_blocks; struct stmpe_variant_block* blocks; } ;
struct stmpe_variant_block {unsigned int block; TYPE_2__* cell; scalar_t__ irq; } ;
struct stmpe {int /*<<< orphan*/  dev; TYPE_1__* pdata; struct stmpe_variant_info* variant; } ;
struct resource {int flags; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_4__ {int num_resources; int /*<<< orphan*/ * resources; } ;
struct TYPE_3__ {unsigned int blocks; } ;

/* Variables and functions */
 int EINVAL ; 
 int IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int stmpe_add_device (struct stmpe*,TYPE_2__*) ; 

__attribute__((used)) static int stmpe_devices_init(struct stmpe *stmpe)
{
	struct stmpe_variant_info *variant = stmpe->variant;
	unsigned int platform_blocks = stmpe->pdata->blocks;
	int ret = -EINVAL;
	int i, j;

	for (i = 0; i < variant->num_blocks; i++) {
		struct stmpe_variant_block *block = &variant->blocks[i];

		if (!(platform_blocks & block->block))
			continue;

		for (j = 0; j < block->cell->num_resources; j++) {
			struct resource *res =
				(struct resource *) &block->cell->resources[j];

			/* Dynamically fill in a variant's IRQ. */
			if (res->flags & IORESOURCE_IRQ)
				res->start = res->end = block->irq + j;
		}

		platform_blocks &= ~block->block;
		ret = stmpe_add_device(stmpe, block->cell);
		if (ret)
			return ret;
	}

	if (platform_blocks)
		dev_warn(stmpe->dev,
			 "platform wants blocks (%#x) not present on variant",
			 platform_blocks);

	return ret;
}