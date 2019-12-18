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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uverbs_req_notify_cq {scalar_t__ solicited_only; int /*<<< orphan*/  cq_handle; } ;
struct ib_cq {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  IB_CQ_SOLICITED ; 
 int /*<<< orphan*/  UVERBS_OBJECT_CQ ; 
 int /*<<< orphan*/  ib_req_notify_cq (struct ib_cq*,int /*<<< orphan*/ ) ; 
 struct ib_cq* uobj_get_obj_read (struct ib_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_cq*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_req_notify_cq*,int) ; 

__attribute__((used)) static int ib_uverbs_req_notify_cq(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_req_notify_cq cmd;
	struct ib_cq                  *cq;
	int ret;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	cq = uobj_get_obj_read(cq, UVERBS_OBJECT_CQ, cmd.cq_handle, attrs);
	if (!cq)
		return -EINVAL;

	ib_req_notify_cq(cq, cmd.solicited_only ?
			 IB_CQ_SOLICITED : IB_CQ_NEXT_COMP);

	uobj_put_obj_read(cq);

	return 0;
}