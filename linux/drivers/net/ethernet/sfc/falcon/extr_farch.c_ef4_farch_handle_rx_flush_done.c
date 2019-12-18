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
struct ef4_rx_queue {int flush_pending; } ;
struct ef4_nic {int n_channels; int /*<<< orphan*/  flush_wq; int /*<<< orphan*/  rxq_flush_outstanding; int /*<<< orphan*/  rxq_flush_pending; int /*<<< orphan*/  net_dev; } ;
struct ef4_channel {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_CHANNEL_MAGIC_RX_DRAIN (struct ef4_rx_queue*) ; 
 int EF4_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSF_AZ_DRIVER_EV_RX_DESCQ_ID ; 
 int /*<<< orphan*/  FSF_AZ_DRIVER_EV_RX_FLUSH_FAIL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ef4_rx_queue* ef4_channel_get_rx_queue (struct ef4_channel*) ; 
 int /*<<< orphan*/  ef4_channel_has_rx_queue (struct ef4_channel*) ; 
 scalar_t__ ef4_farch_flush_wake (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_farch_magic_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ef4_channel* ef4_get_channel (struct ef4_nic*,int) ; 
 int /*<<< orphan*/  ef4_rx_queue_channel (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_info (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ef4_farch_handle_rx_flush_done(struct ef4_nic *efx, ef4_qword_t *event)
{
	struct ef4_channel *channel;
	struct ef4_rx_queue *rx_queue;
	int qid;
	bool failed;

	qid = EF4_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_RX_DESCQ_ID);
	failed = EF4_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_RX_FLUSH_FAIL);
	if (qid >= efx->n_channels)
		return;
	channel = ef4_get_channel(efx, qid);
	if (!ef4_channel_has_rx_queue(channel))
		return;
	rx_queue = ef4_channel_get_rx_queue(channel);

	if (failed) {
		netif_info(efx, hw, efx->net_dev,
			   "RXQ %d flush retry\n", qid);
		rx_queue->flush_pending = true;
		atomic_inc(&efx->rxq_flush_pending);
	} else {
		ef4_farch_magic_event(ef4_rx_queue_channel(rx_queue),
				      EF4_CHANNEL_MAGIC_RX_DRAIN(rx_queue));
	}
	atomic_dec(&efx->rxq_flush_outstanding);
	if (ef4_farch_flush_wake(efx))
		wake_up(&efx->flush_wq);
}