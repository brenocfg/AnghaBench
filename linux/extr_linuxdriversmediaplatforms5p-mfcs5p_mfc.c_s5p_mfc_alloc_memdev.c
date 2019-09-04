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
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  release; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/  bus; struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ device_add (struct device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 struct device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int of_reserved_mem_device_init_by_idx (struct device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  s5p_mfc_memdev_release ; 

__attribute__((used)) static struct device *s5p_mfc_alloc_memdev(struct device *dev,
					   const char *name, unsigned int idx)
{
	struct device *child;
	int ret;

	child = devm_kzalloc(dev, sizeof(*child), GFP_KERNEL);
	if (!child)
		return NULL;

	device_initialize(child);
	dev_set_name(child, "%s:%s", dev_name(dev), name);
	child->parent = dev;
	child->bus = dev->bus;
	child->coherent_dma_mask = dev->coherent_dma_mask;
	child->dma_mask = dev->dma_mask;
	child->release = s5p_mfc_memdev_release;

	if (device_add(child) == 0) {
		ret = of_reserved_mem_device_init_by_idx(child, dev->of_node,
							 idx);
		if (ret == 0)
			return child;
		device_del(child);
	}

	put_device(child);
	return NULL;
}