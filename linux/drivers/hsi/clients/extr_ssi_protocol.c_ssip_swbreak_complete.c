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
struct ssi_protocol {int /*<<< orphan*/  netdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_usecnt; int /*<<< orphan*/  txqueue; } ;
struct hsi_msg {struct hsi_client* cl; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_IDLE ; 
 int /*<<< orphan*/  SEND_READY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_stop_tx (struct hsi_client*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_release_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_set_txstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_xmit (struct hsi_client*) ; 

__attribute__((used)) static void ssip_swbreak_complete(struct hsi_msg *msg)
{
	struct hsi_client *cl = msg->cl;
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);

	ssip_release_cmd(msg);
	spin_lock_bh(&ssi->lock);
	if (list_empty(&ssi->txqueue)) {
		if (atomic_read(&ssi->tx_usecnt)) {
			ssip_set_txstate(ssi, SEND_READY);
		} else {
			ssip_set_txstate(ssi, SEND_IDLE);
			hsi_stop_tx(cl);
		}
		spin_unlock_bh(&ssi->lock);
	} else {
		spin_unlock_bh(&ssi->lock);
		ssip_xmit(cl);
	}
	netif_wake_queue(ssi->netdev);
}