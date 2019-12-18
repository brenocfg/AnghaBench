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
typedef  int /*<<< orphan*/  u64 ;
struct rproc_mem_entry {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct rproc {TYPE_1__ dev; } ;
struct reserved_mem {scalar_t__ base; int /*<<< orphan*/  size; } ;
struct of_phandle_iterator {TYPE_2__* node; } ;
struct firmware {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  of_phandle_iterator_init (struct of_phandle_iterator*,struct device_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ of_phandle_iterator_next (struct of_phandle_iterator*) ; 
 struct reserved_mem* of_reserved_mem_lookup (TYPE_2__*) ; 
 int /*<<< orphan*/  rproc_add_carveout (struct rproc*,struct rproc_mem_entry*) ; 
 int /*<<< orphan*/  rproc_coredump_add_segment (struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rproc_mem_entry* rproc_mem_entry_init (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rproc_mem_entry* rproc_of_resm_mem_entry_init (struct device*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int stm32_rproc_elf_load_rsc_table (struct rproc*,struct firmware const*) ; 
 int /*<<< orphan*/  stm32_rproc_mem_alloc ; 
 int /*<<< orphan*/  stm32_rproc_mem_release ; 
 scalar_t__ stm32_rproc_pa_to_da (struct rproc*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int stm32_rproc_parse_fw(struct rproc *rproc, const struct firmware *fw)
{
	struct device *dev = rproc->dev.parent;
	struct device_node *np = dev->of_node;
	struct of_phandle_iterator it;
	struct rproc_mem_entry *mem;
	struct reserved_mem *rmem;
	u64 da;
	int index = 0;

	/* Register associated reserved memory regions */
	of_phandle_iterator_init(&it, np, "memory-region", NULL, 0);
	while (of_phandle_iterator_next(&it) == 0) {
		rmem = of_reserved_mem_lookup(it.node);
		if (!rmem) {
			dev_err(dev, "unable to acquire memory-region\n");
			return -EINVAL;
		}

		if (stm32_rproc_pa_to_da(rproc, rmem->base, &da) < 0) {
			dev_err(dev, "memory region not valid %pa\n",
				&rmem->base);
			return -EINVAL;
		}

		/*  No need to map vdev buffer */
		if (strcmp(it.node->name, "vdev0buffer")) {
			/* Register memory region */
			mem = rproc_mem_entry_init(dev, NULL,
						   (dma_addr_t)rmem->base,
						   rmem->size, da,
						   stm32_rproc_mem_alloc,
						   stm32_rproc_mem_release,
						   it.node->name);

			if (mem)
				rproc_coredump_add_segment(rproc, da,
							   rmem->size);
		} else {
			/* Register reserved memory for vdev buffer alloc */
			mem = rproc_of_resm_mem_entry_init(dev, index,
							   rmem->size,
							   rmem->base,
							   it.node->name);
		}

		if (!mem)
			return -ENOMEM;

		rproc_add_carveout(rproc, mem);
		index++;
	}

	return stm32_rproc_elf_load_rsc_table(rproc, fw);
}