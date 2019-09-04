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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  compare_of ; 
 int component_master_add_with_match (struct device*,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  devm_of_platform_populate (struct device*) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_of_component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device_node*) ; 
 struct device_node* of_get_next_available_child (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  sti_ops ; 

__attribute__((used)) static int sti_platform_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct device_node *child_np;
	struct component_match *match = NULL;

	dma_set_coherent_mask(dev, DMA_BIT_MASK(32));

	devm_of_platform_populate(dev);

	child_np = of_get_next_available_child(node, NULL);

	while (child_np) {
		drm_of_component_match_add(dev, &match, compare_of,
					   child_np);
		child_np = of_get_next_available_child(node, child_np);
	}

	return component_master_add_with_match(dev, &sti_ops, match);
}