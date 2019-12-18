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
struct cs_hsi_iface {int wakeline_state; TYPE_1__* cl; int /*<<< orphan*/  master; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_slave_start_tx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_slave_stop_tx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_hsi_set_wakeline(struct cs_hsi_iface *hi, bool new_state)
{
	int change = 0;

	spin_lock_bh(&hi->lock);
	if (hi->wakeline_state != new_state) {
		hi->wakeline_state = new_state;
		change = 1;
		dev_dbg(&hi->cl->device, "setting wake line to %d (%p)\n",
			new_state, hi->cl);
	}
	spin_unlock_bh(&hi->lock);

	if (change) {
		if (new_state)
			ssip_slave_start_tx(hi->master);
		else
			ssip_slave_stop_tx(hi->master);
	}

	dev_dbg(&hi->cl->device, "wake line set to %d (%p)\n",
		new_state, hi->cl);
}