#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_6__ {scalar_t__ num_log_addrs; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  fhs; scalar_t__ unregistered; } ;
struct cec_adapter {scalar_t__ phys_addr; int transmit_in_progress; int last_initiator; TYPE_3__ log_addrs; TYPE_2__ devnode; TYPE_1__* ops; scalar_t__ needs_hpd; scalar_t__ monitor_all_cnt; int /*<<< orphan*/  kthread_waitq; } ;
struct TYPE_4__ {scalar_t__ (* adap_enable ) (struct cec_adapter*,int) ;} ;

/* Variables and functions */
 scalar_t__ CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  adap_monitor_all_enable ; 
 scalar_t__ call_op (struct cec_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cec_adap_unconfigure (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_claim_log_addrs (struct cec_adapter*,int) ; 
 int /*<<< orphan*/  cec_phys_addr_exp (scalar_t__) ; 
 int /*<<< orphan*/  cec_post_state_event (struct cec_adapter*) ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct cec_adapter*,int) ; 
 scalar_t__ stub2 (struct cec_adapter*,int) ; 
 scalar_t__ stub3 (struct cec_adapter*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void __cec_s_phys_addr(struct cec_adapter *adap, u16 phys_addr, bool block)
{
	if (phys_addr == adap->phys_addr)
		return;
	if (phys_addr != CEC_PHYS_ADDR_INVALID && adap->devnode.unregistered)
		return;

	dprintk(1, "new physical address %x.%x.%x.%x\n",
		cec_phys_addr_exp(phys_addr));
	if (phys_addr == CEC_PHYS_ADDR_INVALID ||
	    adap->phys_addr != CEC_PHYS_ADDR_INVALID) {
		adap->phys_addr = CEC_PHYS_ADDR_INVALID;
		cec_post_state_event(adap);
		cec_adap_unconfigure(adap);
		/* Disabling monitor all mode should always succeed */
		if (adap->monitor_all_cnt)
			WARN_ON(call_op(adap, adap_monitor_all_enable, false));
		mutex_lock(&adap->devnode.lock);
		if (adap->needs_hpd || list_empty(&adap->devnode.fhs)) {
			WARN_ON(adap->ops->adap_enable(adap, false));
			adap->transmit_in_progress = false;
			wake_up_interruptible(&adap->kthread_waitq);
		}
		mutex_unlock(&adap->devnode.lock);
		if (phys_addr == CEC_PHYS_ADDR_INVALID)
			return;
	}

	mutex_lock(&adap->devnode.lock);
	adap->last_initiator = 0xff;
	adap->transmit_in_progress = false;

	if ((adap->needs_hpd || list_empty(&adap->devnode.fhs)) &&
	    adap->ops->adap_enable(adap, true)) {
		mutex_unlock(&adap->devnode.lock);
		return;
	}

	if (adap->monitor_all_cnt &&
	    call_op(adap, adap_monitor_all_enable, true)) {
		if (adap->needs_hpd || list_empty(&adap->devnode.fhs))
			WARN_ON(adap->ops->adap_enable(adap, false));
		mutex_unlock(&adap->devnode.lock);
		return;
	}
	mutex_unlock(&adap->devnode.lock);

	adap->phys_addr = phys_addr;
	cec_post_state_event(adap);
	if (adap->log_addrs.num_log_addrs)
		cec_claim_log_addrs(adap, block);
}