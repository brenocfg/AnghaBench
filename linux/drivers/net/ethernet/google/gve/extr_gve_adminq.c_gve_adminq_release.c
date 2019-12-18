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
struct gve_priv {TYPE_1__* reg_bar0; } ;
struct TYPE_2__ {int /*<<< orphan*/  adminq_pfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GVE_ADMINQ_SLEEP_LEN ; 
 int GVE_MAX_ADMINQ_RELEASE_CHECK ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  gve_clear_admin_queue_ok (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_clear_device_resources_ok (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_clear_device_rings_ok (struct gve_priv*) ; 
 scalar_t__ ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

void gve_adminq_release(struct gve_priv *priv)
{
	int i = 0;

	/* Tell the device the adminq is leaving */
	iowrite32be(0x0, &priv->reg_bar0->adminq_pfn);
	while (ioread32be(&priv->reg_bar0->adminq_pfn)) {
		/* If this is reached the device is unrecoverable and still
		 * holding memory. Continue looping to avoid memory corruption,
		 * but WARN so it is visible what is going on.
		 */
		if (i == GVE_MAX_ADMINQ_RELEASE_CHECK)
			WARN(1, "Unrecoverable platform error!");
		i++;
		msleep(GVE_ADMINQ_SLEEP_LEN);
	}
	gve_clear_device_rings_ok(priv);
	gve_clear_device_resources_ok(priv);
	gve_clear_admin_queue_ok(priv);
}