#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; } ;
struct ib_uverbs_reg_mr_resp {int /*<<< orphan*/  mr_handle; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct ib_uverbs_reg_mr {int start; int hca_va; int access_flags; int /*<<< orphan*/  length; int /*<<< orphan*/  pd_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct ib_uobject {int /*<<< orphan*/  id; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; struct ib_uobject* object; TYPE_4__ res; struct ib_uobject* uobject; int /*<<< orphan*/ * sig_attrs; int /*<<< orphan*/ * dm; int /*<<< orphan*/  type; struct ib_pd* pd; TYPE_3__* device; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_3__* device; } ;
struct ib_mr {int /*<<< orphan*/  id; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; struct ib_mr* object; TYPE_4__ res; struct ib_mr* uobject; int /*<<< orphan*/ * sig_attrs; int /*<<< orphan*/ * dm; int /*<<< orphan*/  type; struct ib_pd* pd; TYPE_3__* device; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {struct ib_uobject* (* reg_user_mr ) (struct ib_pd*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int device_cap_flags; } ;
struct TYPE_7__ {TYPE_2__ ops; TYPE_1__ attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_ACCESS_ON_DEMAND ; 
 int IB_DEVICE_ON_DEMAND_PAGING ; 
 int /*<<< orphan*/  IB_MR_TYPE_USER ; 
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int PAGE_MASK ; 
 int PTR_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_MR ; 
 int /*<<< orphan*/  UVERBS_OBJECT_MR ; 
 int /*<<< orphan*/  UVERBS_OBJECT_PD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ib_check_mr_access (int) ; 
 int /*<<< orphan*/  ib_dereg_mr_user (struct ib_uobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_uverbs_reg_mr_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rdma_restrack_uadd (TYPE_4__*) ; 
 struct ib_uobject* stub1 (struct ib_pd*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 struct ib_uobject* uobj_alloc (int /*<<< orphan*/ ,struct uverbs_attr_bundle*,struct ib_device**) ; 
 int /*<<< orphan*/  uobj_alloc_abort (struct ib_uobject*,struct uverbs_attr_bundle*) ; 
 int uobj_alloc_commit (struct ib_uobject*,struct uverbs_attr_bundle*) ; 
 struct ib_pd* uobj_get_obj_read (struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_pd*) ; 
 int /*<<< orphan*/  uverbs_get_cleared_udata (struct uverbs_attr_bundle*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_reg_mr*,int) ; 
 int uverbs_response (struct uverbs_attr_bundle*,struct ib_uverbs_reg_mr_resp*,int) ; 

__attribute__((used)) static int ib_uverbs_reg_mr(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_reg_mr      cmd;
	struct ib_uverbs_reg_mr_resp resp;
	struct ib_uobject           *uobj;
	struct ib_pd                *pd;
	struct ib_mr                *mr;
	int                          ret;
	struct ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	if ((cmd.start & ~PAGE_MASK) != (cmd.hca_va & ~PAGE_MASK))
		return -EINVAL;

	ret = ib_check_mr_access(cmd.access_flags);
	if (ret)
		return ret;

	uobj = uobj_alloc(UVERBS_OBJECT_MR, attrs, &ib_dev);
	if (IS_ERR(uobj))
		return PTR_ERR(uobj);

	pd = uobj_get_obj_read(pd, UVERBS_OBJECT_PD, cmd.pd_handle, attrs);
	if (!pd) {
		ret = -EINVAL;
		goto err_free;
	}

	if (cmd.access_flags & IB_ACCESS_ON_DEMAND) {
		if (!(pd->device->attrs.device_cap_flags &
		      IB_DEVICE_ON_DEMAND_PAGING)) {
			pr_debug("ODP support not available\n");
			ret = -EINVAL;
			goto err_put;
		}
	}

	mr = pd->device->ops.reg_user_mr(pd, cmd.start, cmd.length, cmd.hca_va,
					 cmd.access_flags,
					 &attrs->driver_udata);
	if (IS_ERR(mr)) {
		ret = PTR_ERR(mr);
		goto err_put;
	}

	mr->device  = pd->device;
	mr->pd      = pd;
	mr->type    = IB_MR_TYPE_USER;
	mr->dm	    = NULL;
	mr->sig_attrs = NULL;
	mr->uobject = uobj;
	atomic_inc(&pd->usecnt);
	mr->res.type = RDMA_RESTRACK_MR;
	rdma_restrack_uadd(&mr->res);

	uobj->object = mr;

	memset(&resp, 0, sizeof resp);
	resp.lkey      = mr->lkey;
	resp.rkey      = mr->rkey;
	resp.mr_handle = uobj->id;

	ret = uverbs_response(attrs, &resp, sizeof(resp));
	if (ret)
		goto err_copy;

	uobj_put_obj_read(pd);

	return uobj_alloc_commit(uobj, attrs);

err_copy:
	ib_dereg_mr_user(mr, uverbs_get_cleared_udata(attrs));

err_put:
	uobj_put_obj_read(pd);

err_free:
	uobj_alloc_abort(uobj, attrs);
	return ret;
}