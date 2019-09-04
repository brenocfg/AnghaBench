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
struct omap_ssi_port {int /*<<< orphan*/  pdev; int /*<<< orphan*/  wk_lock; scalar_t__ wk_refcount; } ;
struct omap_ssi_controller {scalar_t__ sys; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct hsi_port {int /*<<< orphan*/  num; TYPE_1__ device; } ;
struct hsi_controller {int dummy; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SSI_CLEAR_WAKE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSI_WAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,scalar_t__) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct hsi_controller* to_hsi_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ssi_stop_tx(struct hsi_client *cl)
{
	struct hsi_port *port = hsi_get_port(cl);
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	struct hsi_controller *ssi = to_hsi_controller(port->device.parent);
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	dev_dbg(&port->device, "Wake out low %d\n", omap_port->wk_refcount);

	spin_lock_bh(&omap_port->wk_lock);
	BUG_ON(!omap_port->wk_refcount);
	if (--omap_port->wk_refcount) {
		spin_unlock_bh(&omap_port->wk_lock);
		return 0;
	}
	writel(SSI_WAKE(0), omap_ssi->sys + SSI_CLEAR_WAKE_REG(port->num));
	spin_unlock_bh(&omap_port->wk_lock);

	pm_runtime_mark_last_busy(omap_port->pdev);
	pm_runtime_put_autosuspend(omap_port->pdev); /* Release clocks */


	return 0;
}