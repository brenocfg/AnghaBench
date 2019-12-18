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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mcast_req {size_t func; int /*<<< orphan*/  func_list; int /*<<< orphan*/  group_list; int /*<<< orphan*/  sa_mad; scalar_t__ clean; } ;
struct mcast_group {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_pend_reqs; int /*<<< orphan*/  join_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_leave (struct mcast_group*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcast_req*) ; 
 int /*<<< orphan*/  leave_group (struct mcast_group*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_reply_to_slave (size_t,struct mcast_group*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_leave_req(struct mcast_group *group, u8 leave_mask,
			    struct mcast_req *req)
{
	u16 status;

	if (req->clean)
		leave_mask = group->func[req->func].join_state;

	status = check_leave(group, req->func, leave_mask);
	if (!status)
		leave_group(group, req->func, leave_mask);

	if (!req->clean)
		send_reply_to_slave(req->func, group, &req->sa_mad, status);
	--group->func[req->func].num_pend_reqs;
	list_del(&req->group_list);
	list_del(&req->func_list);
	kfree(req);
	return 1;
}