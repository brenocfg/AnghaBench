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
typedef  int /*<<< orphan*/  u32 ;
struct ssi_protocol {scalar_t__ main_state; int /*<<< orphan*/  netdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_wd; int /*<<< orphan*/  flags; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ ACTIVE ; 
 scalar_t__ HANDSHAKE ; 
 unsigned int SSIP_PAYLOAD (int /*<<< orphan*/ ) ; 
 unsigned int SSIP_WAKETEST_FAILED ; 
 int /*<<< orphan*/  SSIP_WAKETEST_FLAG ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,char*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_waketest (struct hsi_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_error (struct hsi_client*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssip_rx_waketest(struct hsi_client *cl, u32 cmd)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	unsigned int wkres = SSIP_PAYLOAD(cmd);

	spin_lock_bh(&ssi->lock);
	if (ssi->main_state != HANDSHAKE) {
		dev_dbg(&cl->device, "wake lines test ignored M(%d)\n",
							ssi->main_state);
		spin_unlock_bh(&ssi->lock);
		return;
	}
	spin_unlock_bh(&ssi->lock);

	if (test_and_clear_bit(SSIP_WAKETEST_FLAG, &ssi->flags))
		ssi_waketest(cl, 0); /* FIXME: To be removed */

	spin_lock_bh(&ssi->lock);
	ssi->main_state = ACTIVE;
	del_timer(&ssi->tx_wd); /* Stop boot handshake timer */
	spin_unlock_bh(&ssi->lock);

	dev_notice(&cl->device, "WAKELINES TEST %s\n",
				wkres & SSIP_WAKETEST_FAILED ? "FAILED" : "OK");
	if (wkres & SSIP_WAKETEST_FAILED) {
		ssip_error(cl);
		return;
	}
	dev_dbg(&cl->device, "CMT is ONLINE\n");
	netif_wake_queue(ssi->netdev);
	netif_carrier_on(ssi->netdev);
}