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
 int /*<<< orphan*/  SEND_IDLE ; 
 scalar_t__ SEND_READY ; 
 scalar_t__ WAIT4READY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_stop_tx (struct hsi_client*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_set_txstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 

int ssip_slave_stop_tx(struct hsi_client *master)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(master);

	WARN_ON_ONCE(atomic_read(&ssi->tx_usecnt) == 0);

	if (atomic_dec_and_test(&ssi->tx_usecnt)) {
		spin_lock_bh(&ssi->lock);
		if ((ssi->send_state == SEND_READY) ||
			(ssi->send_state == WAIT4READY)) {
			ssip_set_txstate(ssi, SEND_IDLE);
			hsi_stop_tx(master);
		}
		spin_unlock_bh(&ssi->lock);
	}
	dev_dbg(&master->device, "stop TX %d\n", atomic_read(&ssi->tx_usecnt));

	return 0;
}