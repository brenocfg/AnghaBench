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
struct ssi_protocol {scalar_t__ main_state; int /*<<< orphan*/  lock; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ ACTIVE ; 
 int /*<<< orphan*/  RECV_IDLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_set_rxstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssip_stop_rx(struct hsi_client *cl)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);

	dev_dbg(&cl->device, "RX stop M(%d)\n", ssi->main_state);
	spin_lock_bh(&ssi->lock);
	if (likely(ssi->main_state == ACTIVE))
		ssip_set_rxstate(ssi, RECV_IDLE);
	spin_unlock_bh(&ssi->lock);
}