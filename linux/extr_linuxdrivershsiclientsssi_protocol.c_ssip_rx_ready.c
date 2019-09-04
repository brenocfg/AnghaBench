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
struct ssi_protocol {scalar_t__ main_state; scalar_t__ send_state; int /*<<< orphan*/  lock; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ ACTIVE ; 
 int /*<<< orphan*/  SEND_READY ; 
 scalar_t__ WAIT4READY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_set_txstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_xmit (struct hsi_client*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ssip_rx_ready(struct hsi_client *cl)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);

	spin_lock_bh(&ssi->lock);
	if (unlikely(ssi->main_state != ACTIVE)) {
		dev_dbg(&cl->device, "READY on wrong state: S(%d) M(%d)\n",
					ssi->send_state, ssi->main_state);
		spin_unlock_bh(&ssi->lock);
		return;
	}
	if (ssi->send_state != WAIT4READY) {
		dev_dbg(&cl->device, "Ignore spurious READY command\n");
		spin_unlock_bh(&ssi->lock);
		return;
	}
	ssip_set_txstate(ssi, SEND_READY);
	spin_unlock_bh(&ssi->lock);
	ssip_xmit(cl);
}