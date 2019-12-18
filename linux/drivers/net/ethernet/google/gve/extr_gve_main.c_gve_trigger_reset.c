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
struct gve_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_adminq_release (struct gve_priv*) ; 

__attribute__((used)) static void gve_trigger_reset(struct gve_priv *priv)
{
	/* Reset the device by releasing the AQ */
	gve_adminq_release(priv);
}