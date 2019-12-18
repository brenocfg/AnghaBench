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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_ssi_port {size_t port_id; int /*<<< orphan*/  errqueue_work; } ;
struct omap_ssi_controller {int /*<<< orphan*/ ** port; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct hsi_port {void* release; void* stop_tx; void* start_tx; void* flush; void* setup; int /*<<< orphan*/  async; TYPE_1__ device; } ;
struct hsi_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 void* hsi_dummy_cl ; 
 int /*<<< orphan*/  hsi_dummy_msg ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  hsi_port_unregister_clients (struct hsi_port*) ; 
 struct hsi_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_debug_remove_port (struct hsi_port*) ; 
 struct hsi_controller* to_hsi_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssi_port_remove(struct platform_device *pd)
{
	struct hsi_port *port = platform_get_drvdata(pd);
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	struct hsi_controller *ssi = to_hsi_controller(port->device.parent);
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

#ifdef CONFIG_DEBUG_FS
	ssi_debug_remove_port(port);
#endif

	cancel_delayed_work_sync(&omap_port->errqueue_work);

	hsi_port_unregister_clients(port);

	port->async	= hsi_dummy_msg;
	port->setup	= hsi_dummy_cl;
	port->flush	= hsi_dummy_cl;
	port->start_tx	= hsi_dummy_cl;
	port->stop_tx	= hsi_dummy_cl;
	port->release	= hsi_dummy_cl;

	omap_ssi->port[omap_port->port_id] = NULL;
	platform_set_drvdata(pd, NULL);

	pm_runtime_dont_use_autosuspend(&pd->dev);
	pm_runtime_disable(&pd->dev);

	return 0;
}