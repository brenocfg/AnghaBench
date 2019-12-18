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
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; } ;
struct ib_wq_attr {int /*<<< orphan*/  flags_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  wq_state; int /*<<< orphan*/  curr_wq_state; } ;
struct ib_wq {TYPE_2__* device; } ;
struct ib_uverbs_ex_modify_wq {int attr_mask; int /*<<< orphan*/  flags_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  wq_state; int /*<<< orphan*/  curr_wq_state; int /*<<< orphan*/  wq_handle; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int (* modify_wq ) (struct ib_wq*,struct ib_wq_attr*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_WQ_CUR_STATE ; 
 int IB_WQ_FLAGS ; 
 int IB_WQ_STATE ; 
 int /*<<< orphan*/  UVERBS_OBJECT_WQ ; 
 int stub1 (struct ib_wq*,struct ib_wq_attr*,int,int /*<<< orphan*/ *) ; 
 struct ib_wq* uobj_get_obj_read (struct ib_wq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_wq*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_ex_modify_wq*,int) ; 

__attribute__((used)) static int ib_uverbs_ex_modify_wq(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_ex_modify_wq cmd;
	struct ib_wq *wq;
	struct ib_wq_attr wq_attr = {};
	int ret;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	if (!cmd.attr_mask)
		return -EINVAL;

	if (cmd.attr_mask > (IB_WQ_STATE | IB_WQ_CUR_STATE | IB_WQ_FLAGS))
		return -EINVAL;

	wq = uobj_get_obj_read(wq, UVERBS_OBJECT_WQ, cmd.wq_handle, attrs);
	if (!wq)
		return -EINVAL;

	wq_attr.curr_wq_state = cmd.curr_wq_state;
	wq_attr.wq_state = cmd.wq_state;
	if (cmd.attr_mask & IB_WQ_FLAGS) {
		wq_attr.flags = cmd.flags;
		wq_attr.flags_mask = cmd.flags_mask;
	}
	ret = wq->device->ops.modify_wq(wq, &wq_attr, cmd.attr_mask,
					&attrs->driver_udata);
	uobj_put_obj_read(wq);
	return ret;
}