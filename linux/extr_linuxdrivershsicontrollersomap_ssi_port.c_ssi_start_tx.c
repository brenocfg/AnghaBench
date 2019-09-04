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
struct omap_ssi_port {int /*<<< orphan*/  work; int /*<<< orphan*/  wk_lock; int /*<<< orphan*/  wk_refcount; } ;
struct hsi_port {int /*<<< orphan*/  device; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssi_start_tx(struct hsi_client *cl)
{
	struct hsi_port *port = hsi_get_port(cl);
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);

	dev_dbg(&port->device, "Wake out high %d\n", omap_port->wk_refcount);

	spin_lock_bh(&omap_port->wk_lock);
	if (omap_port->wk_refcount++) {
		spin_unlock_bh(&omap_port->wk_lock);
		return 0;
	}
	spin_unlock_bh(&omap_port->wk_lock);

	schedule_work(&omap_port->work);

	return 0;
}