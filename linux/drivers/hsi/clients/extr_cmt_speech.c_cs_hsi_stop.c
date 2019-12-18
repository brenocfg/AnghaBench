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
struct cs_hsi_iface {int /*<<< orphan*/  lock; int /*<<< orphan*/  pm_qos_req; int /*<<< orphan*/  data_state; int /*<<< orphan*/  control_state; TYPE_1__* cl; int /*<<< orphan*/  iface_state; int /*<<< orphan*/  master; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_STATE_CLOSED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cs_free_cmds (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_hsi_free_data (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_hsi_set_wakeline (struct cs_hsi_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_state_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hsi_release_port (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_qos_request_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_slave_put_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_hsi_stop(struct cs_hsi_iface *hi)
{
	dev_dbg(&hi->cl->device, "cs_hsi_stop\n");
	cs_hsi_set_wakeline(hi, 0);
	ssip_slave_put_master(hi->master);

	/* hsi_release_port() needs to be called with CS_STATE_CLOSED */
	hi->iface_state = CS_STATE_CLOSED;
	hsi_release_port(hi->cl);

	/*
	 * hsi_release_port() should flush out all the pending
	 * messages, so cs_state_idle() should be true for both
	 * control and data channels.
	 */
	WARN_ON(!cs_state_idle(hi->control_state));
	WARN_ON(!cs_state_idle(hi->data_state));

	if (pm_qos_request_active(&hi->pm_qos_req))
		pm_qos_remove_request(&hi->pm_qos_req);

	spin_lock_bh(&hi->lock);
	cs_hsi_free_data(hi);
	cs_free_cmds(hi);
	spin_unlock_bh(&hi->lock);
	kfree(hi);
}