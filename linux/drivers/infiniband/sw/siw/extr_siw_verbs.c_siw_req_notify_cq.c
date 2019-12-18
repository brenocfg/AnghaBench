#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct siw_cq {int cq_put; int cq_get; TYPE_1__* notify; } ;
struct ib_cq {int dummy; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int IB_CQ_REPORT_MISSED_EVENTS ; 
 int IB_CQ_SOLICITED ; 
 int IB_CQ_SOLICITED_MASK ; 
 int /*<<< orphan*/  SIW_NOTIFY_ALL ; 
 int /*<<< orphan*/  SIW_NOTIFY_SOLICITED ; 
 int /*<<< orphan*/  siw_dbg_cq (struct siw_cq*,char*,int) ; 
 int /*<<< orphan*/  smp_store_mb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct siw_cq* to_siw_cq (struct ib_cq*) ; 

int siw_req_notify_cq(struct ib_cq *base_cq, enum ib_cq_notify_flags flags)
{
	struct siw_cq *cq = to_siw_cq(base_cq);

	siw_dbg_cq(cq, "flags: 0x%02x\n", flags);

	if ((flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED)
		/*
		 * Enable CQ event for next solicited completion.
		 * and make it visible to all associated producers.
		 */
		smp_store_mb(cq->notify->flags, SIW_NOTIFY_SOLICITED);
	else
		/*
		 * Enable CQ event for any signalled completion.
		 * and make it visible to all associated producers.
		 */
		smp_store_mb(cq->notify->flags, SIW_NOTIFY_ALL);

	if (flags & IB_CQ_REPORT_MISSED_EVENTS)
		return cq->cq_put - cq->cq_get;

	return 0;
}