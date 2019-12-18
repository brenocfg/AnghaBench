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
struct gve_priv {int /*<<< orphan*/  dev; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gve_clear_do_reset (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_clear_reset_in_progress (struct gve_priv*) ; 
 int gve_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_reset_and_teardown (struct gve_priv*,int) ; 
 int gve_reset_recovery (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_set_reset_in_progress (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_teardown_priv_resources (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_turndown (struct gve_priv*) ; 
 int netif_carrier_ok (int /*<<< orphan*/ ) ; 

int gve_reset(struct gve_priv *priv, bool attempt_teardown)
{
	bool was_up = netif_carrier_ok(priv->dev);
	int err;

	dev_info(&priv->pdev->dev, "Performing reset\n");
	gve_clear_do_reset(priv);
	gve_set_reset_in_progress(priv);
	/* If we aren't attempting to teardown normally, just go turndown and
	 * reset right away.
	 */
	if (!attempt_teardown) {
		gve_turndown(priv);
		gve_reset_and_teardown(priv, was_up);
	} else {
		/* Otherwise attempt to close normally */
		if (was_up) {
			err = gve_close(priv->dev);
			/* If that fails reset as we did above */
			if (err)
				gve_reset_and_teardown(priv, was_up);
		}
		/* Clean up any remaining resources */
		gve_teardown_priv_resources(priv);
	}

	/* Set it all back up */
	err = gve_reset_recovery(priv, was_up);
	gve_clear_reset_in_progress(priv);
	return err;
}