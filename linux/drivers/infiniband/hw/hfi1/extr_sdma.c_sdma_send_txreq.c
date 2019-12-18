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
typedef  int /*<<< orphan*/  u16 ;
struct sdma_txreq {int tlen; scalar_t__ num_desc; int /*<<< orphan*/  list; scalar_t__ sn; scalar_t__ next_descq_idx; int /*<<< orphan*/  wait; } ;
struct sdma_engine {scalar_t__ desc_avail; int /*<<< orphan*/  descq_full_count; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  cpu; int /*<<< orphan*/  flushlist_lock; int /*<<< orphan*/  flushlist; int /*<<< orphan*/  tail_sn; int /*<<< orphan*/  tail_lock; } ;
struct iowait_work {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ECOMM ; 
 int EINVAL ; 
 int /*<<< orphan*/  __sdma_running (struct sdma_engine*) ; 
 int /*<<< orphan*/  iowait_inc_wait_count (struct iowait_work*,scalar_t__) ; 
 int /*<<< orphan*/  iowait_ioww_to_iow (struct iowait_work*) ; 
 int /*<<< orphan*/  iowait_sdma_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sdma_check_progress (struct sdma_engine*,struct iowait_work*,struct sdma_txreq*,int) ; 
 int /*<<< orphan*/  sdma_update_tail (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  submit_tx (struct sdma_engine*,struct sdma_txreq*) ; 
 int /*<<< orphan*/  system_highpri_wq ; 
 int /*<<< orphan*/  trace_hfi1_sdma_in_sn (struct sdma_engine*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int sdma_send_txreq(struct sdma_engine *sde,
		    struct iowait_work *wait,
		    struct sdma_txreq *tx,
		    bool pkts_sent)
{
	int ret = 0;
	u16 tail;
	unsigned long flags;

	/* user should have supplied entire packet */
	if (unlikely(tx->tlen))
		return -EINVAL;
	tx->wait = iowait_ioww_to_iow(wait);
	spin_lock_irqsave(&sde->tail_lock, flags);
retry:
	if (unlikely(!__sdma_running(sde)))
		goto unlock_noconn;
	if (unlikely(tx->num_desc > sde->desc_avail))
		goto nodesc;
	tail = submit_tx(sde, tx);
	if (wait)
		iowait_sdma_inc(iowait_ioww_to_iow(wait));
	sdma_update_tail(sde, tail);
unlock:
	spin_unlock_irqrestore(&sde->tail_lock, flags);
	return ret;
unlock_noconn:
	if (wait)
		iowait_sdma_inc(iowait_ioww_to_iow(wait));
	tx->next_descq_idx = 0;
#ifdef CONFIG_HFI1_DEBUG_SDMA_ORDER
	tx->sn = sde->tail_sn++;
	trace_hfi1_sdma_in_sn(sde, tx->sn);
#endif
	spin_lock(&sde->flushlist_lock);
	list_add_tail(&tx->list, &sde->flushlist);
	spin_unlock(&sde->flushlist_lock);
	iowait_inc_wait_count(wait, tx->num_desc);
	queue_work_on(sde->cpu, system_highpri_wq, &sde->flush_worker);
	ret = -ECOMM;
	goto unlock;
nodesc:
	ret = sdma_check_progress(sde, wait, tx, pkts_sent);
	if (ret == -EAGAIN) {
		ret = 0;
		goto retry;
	}
	sde->descq_full_count++;
	goto unlock;
}