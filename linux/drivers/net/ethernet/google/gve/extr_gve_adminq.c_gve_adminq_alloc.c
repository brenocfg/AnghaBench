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
typedef  union gve_adminq_command {int dummy; } gve_adminq_command ;
struct gve_priv {int adminq_bus_addr; int adminq_mask; TYPE_1__* reg_bar0; scalar_t__ adminq_prod_cnt; int /*<<< orphan*/  adminq; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  adminq_pfn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_set_admin_queue_ok (struct gve_priv*) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int gve_adminq_alloc(struct device *dev, struct gve_priv *priv)
{
	priv->adminq = dma_alloc_coherent(dev, PAGE_SIZE,
					  &priv->adminq_bus_addr, GFP_KERNEL);
	if (unlikely(!priv->adminq))
		return -ENOMEM;

	priv->adminq_mask = (PAGE_SIZE / sizeof(union gve_adminq_command)) - 1;
	priv->adminq_prod_cnt = 0;

	/* Setup Admin queue with the device */
	iowrite32be(priv->adminq_bus_addr / PAGE_SIZE,
		    &priv->reg_bar0->adminq_pfn);

	gve_set_admin_queue_ok(priv);
	return 0;
}