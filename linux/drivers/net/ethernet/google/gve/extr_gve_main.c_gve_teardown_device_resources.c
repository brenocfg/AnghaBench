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
struct gve_priv {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gve_adminq_deconfigure_device_resources (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_clear_device_resources_ok (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_counter_array (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_notify_blocks (struct gve_priv*) ; 
 scalar_t__ gve_get_device_resources_ok (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_trigger_reset (struct gve_priv*) ; 

__attribute__((used)) static void gve_teardown_device_resources(struct gve_priv *priv)
{
	int err;

	/* Tell device its resources are being freed */
	if (gve_get_device_resources_ok(priv)) {
		err = gve_adminq_deconfigure_device_resources(priv);
		if (err) {
			dev_err(&priv->pdev->dev,
				"Could not deconfigure device resources: err=%d\n",
				err);
			gve_trigger_reset(priv);
		}
	}
	gve_free_counter_array(priv);
	gve_free_notify_blocks(priv);
	gve_clear_device_resources_ok(priv);
}