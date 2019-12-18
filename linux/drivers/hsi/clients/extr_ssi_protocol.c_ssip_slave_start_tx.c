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
struct ssi_protocol {scalar_t__ send_state; int /*<<< orphan*/  tx_usecnt; int /*<<< orphan*/  lock; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ SEND_IDLE ; 
 int /*<<< orphan*/  WAIT4READY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_start_tx (struct hsi_client*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_set_txstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 

int ssip_slave_start_tx(struct hsi_client *master)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(master);

	dev_dbg(&master->device, "start TX %d\n", atomic_read(&ssi->tx_usecnt));
	spin_lock_bh(&ssi->lock);
	if (ssi->send_state == SEND_IDLE) {
		ssip_set_txstate(ssi, WAIT4READY);
		hsi_start_tx(master);
	}
	spin_unlock_bh(&ssi->lock);
	atomic_inc(&ssi->tx_usecnt);

	return 0;
}