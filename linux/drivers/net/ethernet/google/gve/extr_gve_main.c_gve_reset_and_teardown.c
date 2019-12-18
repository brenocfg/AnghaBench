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
struct gve_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_teardown_priv_resources (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_trigger_reset (struct gve_priv*) ; 

__attribute__((used)) static void gve_reset_and_teardown(struct gve_priv *priv, bool was_up)
{
	gve_trigger_reset(priv);
	/* With the reset having already happened, close cannot fail */
	if (was_up)
		gve_close(priv->dev);
	gve_teardown_priv_resources(priv);
}