#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ib_sa_query {int /*<<< orphan*/  list; scalar_t__ timeout; scalar_t__ seq; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 TYPE_1__ ib_nl_request_list ; 
 int /*<<< orphan*/  ib_nl_request_lock ; 
 int /*<<< orphan*/  ib_nl_sa_request_seq ; 
 int ib_nl_send_msg (struct ib_sa_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_nl_timed_work ; 
 int /*<<< orphan*/  ib_nl_wq ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sa_local_svc_timeout_ms ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ib_nl_make_request(struct ib_sa_query *query, gfp_t gfp_mask)
{
	unsigned long flags;
	unsigned long delay;
	int ret;

	INIT_LIST_HEAD(&query->list);
	query->seq = (u32)atomic_inc_return(&ib_nl_sa_request_seq);

	/* Put the request on the list first.*/
	spin_lock_irqsave(&ib_nl_request_lock, flags);
	delay = msecs_to_jiffies(sa_local_svc_timeout_ms);
	query->timeout = delay + jiffies;
	list_add_tail(&query->list, &ib_nl_request_list);
	/* Start the timeout if this is the only request */
	if (ib_nl_request_list.next == &query->list)
		queue_delayed_work(ib_nl_wq, &ib_nl_timed_work, delay);
	spin_unlock_irqrestore(&ib_nl_request_lock, flags);

	ret = ib_nl_send_msg(query, gfp_mask);
	if (ret) {
		ret = -EIO;
		/* Remove the request */
		spin_lock_irqsave(&ib_nl_request_lock, flags);
		list_del(&query->list);
		spin_unlock_irqrestore(&ib_nl_request_lock, flags);
	}

	return ret;
}