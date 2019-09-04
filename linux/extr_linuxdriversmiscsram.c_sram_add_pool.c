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
struct sram_reserve {int /*<<< orphan*/  size; int /*<<< orphan*/  label; } ;
struct sram_partition {scalar_t__ base; int /*<<< orphan*/  pool; } ;
struct sram_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRAM_GRANULARITY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_gen_pool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gen_pool_add_virt (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sram_add_pool(struct sram_dev *sram, struct sram_reserve *block,
			 phys_addr_t start, struct sram_partition *part)
{
	int ret;

	part->pool = devm_gen_pool_create(sram->dev, ilog2(SRAM_GRANULARITY),
					  NUMA_NO_NODE, block->label);
	if (IS_ERR(part->pool))
		return PTR_ERR(part->pool);

	ret = gen_pool_add_virt(part->pool, (unsigned long)part->base, start,
				block->size, NUMA_NO_NODE);
	if (ret < 0) {
		dev_err(sram->dev, "failed to register subpool: %d\n", ret);
		return ret;
	}

	return 0;
}