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
 scalar_t__ gve_get_do_reset (struct gve_priv*) ; 
 scalar_t__ gve_get_probe_in_progress (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_reset (struct gve_priv*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void gve_handle_reset(struct gve_priv *priv)
{
	/* A service task will be scheduled at the end of probe to catch any
	 * resets that need to happen, and we don't want to reset until
	 * probe is done.
	 */
	if (gve_get_probe_in_progress(priv))
		return;

	if (gve_get_do_reset(priv)) {
		rtnl_lock();
		gve_reset(priv, false);
		rtnl_unlock();
	}
}