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
struct ib_uverbs_rereg_mr_resp {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct ib_uverbs_rereg_mr {int flags; int start; int hca_va; scalar_t__ length; int /*<<< orphan*/  access_flags; int /*<<< orphan*/  pd_handle; int /*<<< orphan*/  mr_handle; } ;
struct ib_uobject {struct ib_mr* object; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_mr {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; struct ib_pd* pd; TYPE_2__* device; scalar_t__ dm; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int (* rereg_user_mr ) (struct ib_mr*,int,int,scalar_t__,int,int /*<<< orphan*/ ,struct ib_pd*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_MR_REREG_ACCESS ; 
 int IB_MR_REREG_PD ; 
 int IB_MR_REREG_SUPPORTED ; 
 int IB_MR_REREG_TRANS ; 
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int PAGE_MASK ; 
 int PTR_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  UVERBS_OBJECT_MR ; 
 int /*<<< orphan*/  UVERBS_OBJECT_PD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ib_check_mr_access (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_uverbs_rereg_mr_resp*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ib_mr*,int,int,scalar_t__,int,int /*<<< orphan*/ ,struct ib_pd*,int /*<<< orphan*/ *) ; 
 struct ib_pd* uobj_get_obj_read (struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 struct ib_uobject* uobj_get_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_pd*) ; 
 int /*<<< orphan*/  uobj_put_write (struct ib_uobject*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_rereg_mr*,int) ; 
 int uverbs_response (struct uverbs_attr_bundle*,struct ib_uverbs_rereg_mr_resp*,int) ; 

__attribute__((used)) static int ib_uverbs_rereg_mr(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_rereg_mr      cmd;
	struct ib_uverbs_rereg_mr_resp resp;
	struct ib_pd                *pd = NULL;
	struct ib_mr                *mr;
	struct ib_pd		    *old_pd;
	int                          ret;
	struct ib_uobject	    *uobj;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	if (cmd.flags & ~IB_MR_REREG_SUPPORTED || !cmd.flags)
		return -EINVAL;

	if ((cmd.flags & IB_MR_REREG_TRANS) &&
	    (!cmd.start || !cmd.hca_va || 0 >= cmd.length ||
	     (cmd.start & ~PAGE_MASK) != (cmd.hca_va & ~PAGE_MASK)))
			return -EINVAL;

	uobj = uobj_get_write(UVERBS_OBJECT_MR, cmd.mr_handle, attrs);
	if (IS_ERR(uobj))
		return PTR_ERR(uobj);

	mr = uobj->object;

	if (mr->dm) {
		ret = -EINVAL;
		goto put_uobjs;
	}

	if (cmd.flags & IB_MR_REREG_ACCESS) {
		ret = ib_check_mr_access(cmd.access_flags);
		if (ret)
			goto put_uobjs;
	}

	if (cmd.flags & IB_MR_REREG_PD) {
		pd = uobj_get_obj_read(pd, UVERBS_OBJECT_PD, cmd.pd_handle,
				       attrs);
		if (!pd) {
			ret = -EINVAL;
			goto put_uobjs;
		}
	}

	old_pd = mr->pd;
	ret = mr->device->ops.rereg_user_mr(mr, cmd.flags, cmd.start,
					    cmd.length, cmd.hca_va,
					    cmd.access_flags, pd,
					    &attrs->driver_udata);
	if (ret)
		goto put_uobj_pd;

	if (cmd.flags & IB_MR_REREG_PD) {
		atomic_inc(&pd->usecnt);
		mr->pd = pd;
		atomic_dec(&old_pd->usecnt);
	}

	memset(&resp, 0, sizeof(resp));
	resp.lkey      = mr->lkey;
	resp.rkey      = mr->rkey;

	ret = uverbs_response(attrs, &resp, sizeof(resp));

put_uobj_pd:
	if (cmd.flags & IB_MR_REREG_PD)
		uobj_put_obj_read(pd);

put_uobjs:
	uobj_put_write(uobj);

	return ret;
}