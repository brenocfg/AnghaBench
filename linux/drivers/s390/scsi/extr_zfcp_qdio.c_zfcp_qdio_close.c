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
struct zfcp_qdio {int req_q_idx; int /*<<< orphan*/  req_q_free; int /*<<< orphan*/  req_q; int /*<<< orphan*/  req_q_wq; int /*<<< orphan*/  req_q_lock; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  ccw_device; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDIO_FLAG_CLEANUP_USING_CLEAR ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int ZFCP_STATUS_ADAPTER_QDIOUP ; 
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (int /*<<< orphan*/ ,int,int) ; 

void zfcp_qdio_close(struct zfcp_qdio *qdio)
{
	struct zfcp_adapter *adapter = qdio->adapter;
	int idx, count;

	if (!(atomic_read(&adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP))
		return;

	/* clear QDIOUP flag, thus do_QDIO is not called during qdio_shutdown */
	spin_lock_irq(&qdio->req_q_lock);
	atomic_andnot(ZFCP_STATUS_ADAPTER_QDIOUP, &adapter->status);
	spin_unlock_irq(&qdio->req_q_lock);

	wake_up(&qdio->req_q_wq);

	qdio_shutdown(adapter->ccw_device, QDIO_FLAG_CLEANUP_USING_CLEAR);

	/* cleanup used outbound sbals */
	count = atomic_read(&qdio->req_q_free);
	if (count < QDIO_MAX_BUFFERS_PER_Q) {
		idx = (qdio->req_q_idx + count) % QDIO_MAX_BUFFERS_PER_Q;
		count = QDIO_MAX_BUFFERS_PER_Q - count;
		zfcp_qdio_zero_sbals(qdio->req_q, idx, count);
	}
	qdio->req_q_idx = 0;
	atomic_set(&qdio->req_q_free, 0);
}