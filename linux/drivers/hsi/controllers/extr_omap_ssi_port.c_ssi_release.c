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
struct TYPE_6__ {void* mode; } ;
struct TYPE_5__ {void* mode; } ;
struct omap_ssi_port {scalar_t__ wk_refcount; int /*<<< orphan*/  pdev; int /*<<< orphan*/  lock; TYPE_3__ ssr; TYPE_2__ sst; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct hsi_port {int claimed; TYPE_1__ device; } ;
struct hsi_controller {int dummy; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 void* SSI_MODE_SLEEP ; 
 int /*<<< orphan*/  SSI_WAKE_EN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_cleanup_gdd (struct hsi_controller*,struct hsi_client*) ; 
 int /*<<< orphan*/  ssi_cleanup_queues (struct hsi_client*) ; 
 int /*<<< orphan*/  ssi_set_port_mode (struct omap_ssi_port*,void*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hsi_controller* to_hsi_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssi_release(struct hsi_client *cl)
{
	struct hsi_port *port = hsi_get_port(cl);
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	struct hsi_controller *ssi = to_hsi_controller(port->device.parent);

	pm_runtime_get_sync(omap_port->pdev);
	spin_lock_bh(&omap_port->lock);
	/* Stop all the pending DMA requests for that client */
	ssi_cleanup_gdd(ssi, cl);
	/* Now cleanup all the queues */
	ssi_cleanup_queues(cl);
	/* If it is the last client of the port, do extra checks and cleanup */
	if (port->claimed <= 1) {
		/*
		 * Drop the clock reference for the incoming wake line
		 * if it is still kept high by the other side.
		 */
		if (test_and_clear_bit(SSI_WAKE_EN, &omap_port->flags))
			pm_runtime_put_sync(omap_port->pdev);
		pm_runtime_get(omap_port->pdev);
		/* Stop any SSI TX/RX without a client */
		ssi_set_port_mode(omap_port, SSI_MODE_SLEEP);
		omap_port->sst.mode = SSI_MODE_SLEEP;
		omap_port->ssr.mode = SSI_MODE_SLEEP;
		pm_runtime_put(omap_port->pdev);
		WARN_ON(omap_port->wk_refcount != 0);
	}
	spin_unlock_bh(&omap_port->lock);
	pm_runtime_put_sync(omap_port->pdev);

	return 0;
}