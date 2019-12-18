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
struct ib_uverbs_modify_srq {int /*<<< orphan*/  attr_mask; int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_wr; int /*<<< orphan*/  srq_handle; } ;
struct ib_srq_attr {int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_wr; } ;
struct ib_srq {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int (* modify_srq ) (struct ib_srq*,struct ib_srq_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVERBS_OBJECT_SRQ ; 
 int stub1 (struct ib_srq*,struct ib_srq_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ib_srq* uobj_get_obj_read (struct ib_srq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_srq*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_modify_srq*,int) ; 

__attribute__((used)) static int ib_uverbs_modify_srq(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_modify_srq cmd;
	struct ib_srq              *srq;
	struct ib_srq_attr          attr;
	int                         ret;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	srq = uobj_get_obj_read(srq, UVERBS_OBJECT_SRQ, cmd.srq_handle, attrs);
	if (!srq)
		return -EINVAL;

	attr.max_wr    = cmd.max_wr;
	attr.srq_limit = cmd.srq_limit;

	ret = srq->device->ops.modify_srq(srq, &attr, cmd.attr_mask,
					  &attrs->driver_udata);

	uobj_put_obj_read(srq);

	return ret;
}