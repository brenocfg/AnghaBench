#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_port_number; } ;
struct tb_switch {int /*<<< orphan*/  dev; int /*<<< orphan*/  is_unplugged; TYPE_3__* ports; TYPE_1__ config; scalar_t__ rpm; } ;
struct TYPE_6__ {int /*<<< orphan*/ * xdomain; TYPE_2__* remote; } ;
struct TYPE_5__ {struct tb_switch* sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_lc_unconfigure_link (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_plug_events_active (struct tb_switch*,int) ; 
 scalar_t__ tb_port_has_remote (TYPE_3__*) ; 
 scalar_t__ tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_switch_nvm_remove (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_xdomain_remove (int /*<<< orphan*/ *) ; 

void tb_switch_remove(struct tb_switch *sw)
{
	int i;

	if (sw->rpm) {
		pm_runtime_get_sync(&sw->dev);
		pm_runtime_disable(&sw->dev);
	}

	/* port 0 is the switch itself and never has a remote */
	for (i = 1; i <= sw->config.max_port_number; i++) {
		if (tb_port_has_remote(&sw->ports[i])) {
			tb_switch_remove(sw->ports[i].remote->sw);
			sw->ports[i].remote = NULL;
		} else if (sw->ports[i].xdomain) {
			tb_xdomain_remove(sw->ports[i].xdomain);
			sw->ports[i].xdomain = NULL;
		}
	}

	if (!sw->is_unplugged)
		tb_plug_events_active(sw, false);
	tb_lc_unconfigure_link(sw);

	tb_switch_nvm_remove(sw);

	if (tb_route(sw))
		dev_info(&sw->dev, "device disconnected\n");
	device_unregister(&sw->dev);
}