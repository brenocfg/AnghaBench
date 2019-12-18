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
struct gve_priv {int /*<<< orphan*/  adminq_bus_addr; int /*<<< orphan*/  adminq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_adminq_release (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_clear_admin_queue_ok (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_get_admin_queue_ok (struct gve_priv*) ; 

void gve_adminq_free(struct device *dev, struct gve_priv *priv)
{
	if (!gve_get_admin_queue_ok(priv))
		return;
	gve_adminq_release(priv);
	dma_free_coherent(dev, PAGE_SIZE, priv->adminq, priv->adminq_bus_addr);
	gve_clear_admin_queue_ok(priv);
}