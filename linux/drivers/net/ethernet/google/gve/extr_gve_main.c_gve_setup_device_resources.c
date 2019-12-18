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
struct gve_priv {TYPE_1__* pdev; int /*<<< orphan*/  num_ntfy_blks; int /*<<< orphan*/  ntfy_block_bus; int /*<<< orphan*/  num_event_counters; int /*<<< orphan*/  counter_array_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gve_adminq_configure_device_resources (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gve_alloc_counter_array (struct gve_priv*) ; 
 int gve_alloc_notify_blocks (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_counter_array (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_notify_blocks (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_set_device_resources_ok (struct gve_priv*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gve_setup_device_resources(struct gve_priv *priv)
{
	int err;

	err = gve_alloc_counter_array(priv);
	if (err)
		return err;
	err = gve_alloc_notify_blocks(priv);
	if (err)
		goto abort_with_counter;
	err = gve_adminq_configure_device_resources(priv,
						    priv->counter_array_bus,
						    priv->num_event_counters,
						    priv->ntfy_block_bus,
						    priv->num_ntfy_blks);
	if (unlikely(err)) {
		dev_err(&priv->pdev->dev,
			"could not setup device_resources: err=%d\n", err);
		err = -ENXIO;
		goto abort_with_ntfy_blocks;
	}
	gve_set_device_resources_ok(priv);
	return 0;
abort_with_ntfy_blocks:
	gve_free_notify_blocks(priv);
abort_with_counter:
	gve_free_counter_array(priv);
	return err;
}