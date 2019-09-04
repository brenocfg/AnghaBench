#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_ssi_port {int wktest; } ;
struct omap_ssi_controller {scalar_t__ sys; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct hsi_port {int /*<<< orphan*/  num; TYPE_2__ device; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct hsi_controller {TYPE_1__ device; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ SSI_CLEAR_WAKE_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ SSI_SET_WAKE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSI_WAKE (int /*<<< orphan*/ ) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct hsi_controller* to_hsi_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void ssi_waketest(struct hsi_client *cl, unsigned int enable)
{
	struct hsi_port *port = hsi_get_port(cl);
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	struct hsi_controller *ssi = to_hsi_controller(port->device.parent);
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	omap_port->wktest = !!enable;
	if (omap_port->wktest) {
		pm_runtime_get_sync(ssi->device.parent);
		writel_relaxed(SSI_WAKE(0),
				omap_ssi->sys + SSI_SET_WAKE_REG(port->num));
	} else {
		writel_relaxed(SSI_WAKE(0),
				omap_ssi->sys +	SSI_CLEAR_WAKE_REG(port->num));
		pm_runtime_put(ssi->device.parent);
	}
}