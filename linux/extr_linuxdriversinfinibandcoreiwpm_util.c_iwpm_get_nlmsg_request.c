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
typedef  int /*<<< orphan*/  u8 ;
struct iwpm_nlmsg_request {int /*<<< orphan*/  sem; scalar_t__ err_code; scalar_t__ request_done; int /*<<< orphan*/  nl_client; int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  kref; int /*<<< orphan*/  inprocess_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwpm_nlmsg_req_list ; 
 int /*<<< orphan*/  iwpm_nlmsg_req_lock ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct iwpm_nlmsg_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct iwpm_nlmsg_request *iwpm_get_nlmsg_request(__u32 nlmsg_seq,
					u8 nl_client, gfp_t gfp)
{
	struct iwpm_nlmsg_request *nlmsg_request = NULL;
	unsigned long flags;

	nlmsg_request = kzalloc(sizeof(struct iwpm_nlmsg_request), gfp);
	if (!nlmsg_request)
		return NULL;

	spin_lock_irqsave(&iwpm_nlmsg_req_lock, flags);
	list_add_tail(&nlmsg_request->inprocess_list, &iwpm_nlmsg_req_list);
	spin_unlock_irqrestore(&iwpm_nlmsg_req_lock, flags);

	kref_init(&nlmsg_request->kref);
	kref_get(&nlmsg_request->kref);
	nlmsg_request->nlmsg_seq = nlmsg_seq;
	nlmsg_request->nl_client = nl_client;
	nlmsg_request->request_done = 0;
	nlmsg_request->err_code = 0;
	sema_init(&nlmsg_request->sem, 1);
	down(&nlmsg_request->sem);
	return nlmsg_request;
}