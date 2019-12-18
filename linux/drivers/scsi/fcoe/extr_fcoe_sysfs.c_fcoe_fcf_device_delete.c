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
struct fcoe_fcf_device {int dev_loss_tmo; scalar_t__ state; int /*<<< orphan*/  dev_loss_work; int /*<<< orphan*/ * priv; } ;
struct fcoe_ctlr_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ FCOE_FCF_STATE_CONNECTED ; 
 scalar_t__ FCOE_FCF_STATE_DISCONNECTED ; 
 int HZ ; 
 int /*<<< orphan*/  fcoe_ctlr_device_queue_devloss_work (struct fcoe_ctlr_device*,int /*<<< orphan*/ *,int) ; 
 struct fcoe_ctlr_device* fcoe_fcf_dev_to_ctlr_dev (struct fcoe_fcf_device*) ; 

void fcoe_fcf_device_delete(struct fcoe_fcf_device *fcf)
{
	struct fcoe_ctlr_device *ctlr = fcoe_fcf_dev_to_ctlr_dev(fcf);
	int timeout = fcf->dev_loss_tmo;

	if (fcf->state != FCOE_FCF_STATE_CONNECTED)
		return;

	fcf->state = FCOE_FCF_STATE_DISCONNECTED;

	/*
	 * FCF will only be re-connected by the LLD calling
	 * fcoe_fcf_device_add, and it should be setting up
	 * priv then.
	 */
	fcf->priv = NULL;

	fcoe_ctlr_device_queue_devloss_work(ctlr, &fcf->dev_loss_work,
					   timeout * HZ);
}