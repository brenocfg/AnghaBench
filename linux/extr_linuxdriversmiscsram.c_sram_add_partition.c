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
struct sram_reserve {scalar_t__ protect_exec; scalar_t__ export; scalar_t__ pool; scalar_t__ start; } ;
struct sram_partition {scalar_t__ base; int /*<<< orphan*/  lock; } ;
struct sram_dev {size_t partitions; scalar_t__ virt_base; struct sram_partition* partition; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sram_add_export (struct sram_dev*,struct sram_reserve*,int /*<<< orphan*/ ,struct sram_partition*) ; 
 int sram_add_pool (struct sram_dev*,struct sram_reserve*,int /*<<< orphan*/ ,struct sram_partition*) ; 
 int /*<<< orphan*/  sram_add_protect_exec (struct sram_partition*) ; 
 int sram_check_protect_exec (struct sram_dev*,struct sram_reserve*,struct sram_partition*) ; 

__attribute__((used)) static int sram_add_partition(struct sram_dev *sram, struct sram_reserve *block,
			      phys_addr_t start)
{
	int ret;
	struct sram_partition *part = &sram->partition[sram->partitions];

	mutex_init(&part->lock);
	part->base = sram->virt_base + block->start;

	if (block->pool) {
		ret = sram_add_pool(sram, block, start, part);
		if (ret)
			return ret;
	}
	if (block->export) {
		ret = sram_add_export(sram, block, start, part);
		if (ret)
			return ret;
	}
	if (block->protect_exec) {
		ret = sram_check_protect_exec(sram, block, part);
		if (ret)
			return ret;

		ret = sram_add_pool(sram, block, start, part);
		if (ret)
			return ret;

		sram_add_protect_exec(part);
	}

	sram->partitions++;

	return 0;
}