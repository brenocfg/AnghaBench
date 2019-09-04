#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ log_addr_mask; } ;
struct cec_adapter {scalar_t__ phys_addr; int is_configuring; int is_configured; int /*<<< orphan*/  kthread_waitq; int /*<<< orphan*/  phys_addrs; TYPE_2__ log_addrs; TYPE_1__* ops; int /*<<< orphan*/  needs_hpd; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* adap_log_addr ) (struct cec_adapter*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_LOG_ADDR_INVALID ; 
 scalar_t__ CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_flush (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_post_state_event (struct cec_adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct cec_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cec_adap_unconfigure(struct cec_adapter *adap)
{
	if (!adap->needs_hpd ||
	    adap->phys_addr != CEC_PHYS_ADDR_INVALID)
		WARN_ON(adap->ops->adap_log_addr(adap, CEC_LOG_ADDR_INVALID));
	adap->log_addrs.log_addr_mask = 0;
	adap->is_configuring = false;
	adap->is_configured = false;
	memset(adap->phys_addrs, 0xff, sizeof(adap->phys_addrs));
	cec_flush(adap);
	wake_up_interruptible(&adap->kthread_waitq);
	cec_post_state_event(adap);
}