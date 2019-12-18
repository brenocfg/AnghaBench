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
struct ib_uverbs_alloc_mw_resp {int /*<<< orphan*/  mw_handle; int /*<<< orphan*/  rkey; } ;
struct ib_uverbs_alloc_mw {scalar_t__ mw_type; int /*<<< orphan*/  pd_handle; } ;
struct ib_uobject {int /*<<< orphan*/  id; int /*<<< orphan*/  rkey; struct ib_uobject* object; struct ib_uobject* uobject; struct ib_pd* pd; TYPE_2__* device; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_2__* device; } ;
struct ib_mw {int /*<<< orphan*/  id; int /*<<< orphan*/  rkey; struct ib_mw* object; struct ib_mw* uobject; struct ib_pd* pd; TYPE_2__* device; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {struct ib_uobject* (* alloc_mw ) (struct ib_pd*,scalar_t__,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_MW_TYPE_1 ; 
 scalar_t__ IB_MW_TYPE_2 ; 
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int PTR_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  UVERBS_OBJECT_MW ; 
 int /*<<< orphan*/  UVERBS_OBJECT_PD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ib_uverbs_alloc_mw_resp*,int /*<<< orphan*/ ,int) ; 
 struct ib_uobject* stub1 (struct ib_pd*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct ib_uobject* uobj_alloc (int /*<<< orphan*/ ,struct uverbs_attr_bundle*,struct ib_device**) ; 
 int /*<<< orphan*/  uobj_alloc_abort (struct ib_uobject*,struct uverbs_attr_bundle*) ; 
 int uobj_alloc_commit (struct ib_uobject*,struct uverbs_attr_bundle*) ; 
 struct ib_pd* uobj_get_obj_read (struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_pd*) ; 
 int /*<<< orphan*/  uverbs_dealloc_mw (struct ib_uobject*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_alloc_mw*,int) ; 
 int uverbs_response (struct uverbs_attr_bundle*,struct ib_uverbs_alloc_mw_resp*,int) ; 

__attribute__((used)) static int ib_uverbs_alloc_mw(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_alloc_mw      cmd;
	struct ib_uverbs_alloc_mw_resp resp;
	struct ib_uobject             *uobj;
	struct ib_pd                  *pd;
	struct ib_mw                  *mw;
	int                            ret;
	struct ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	uobj = uobj_alloc(UVERBS_OBJECT_MW, attrs, &ib_dev);
	if (IS_ERR(uobj))
		return PTR_ERR(uobj);

	pd = uobj_get_obj_read(pd, UVERBS_OBJECT_PD, cmd.pd_handle, attrs);
	if (!pd) {
		ret = -EINVAL;
		goto err_free;
	}

	if (cmd.mw_type != IB_MW_TYPE_1 && cmd.mw_type != IB_MW_TYPE_2) {
		ret = -EINVAL;
		goto err_put;
	}

	mw = pd->device->ops.alloc_mw(pd, cmd.mw_type, &attrs->driver_udata);
	if (IS_ERR(mw)) {
		ret = PTR_ERR(mw);
		goto err_put;
	}

	mw->device  = pd->device;
	mw->pd      = pd;
	mw->uobject = uobj;
	atomic_inc(&pd->usecnt);

	uobj->object = mw;

	memset(&resp, 0, sizeof(resp));
	resp.rkey      = mw->rkey;
	resp.mw_handle = uobj->id;

	ret = uverbs_response(attrs, &resp, sizeof(resp));
	if (ret)
		goto err_copy;

	uobj_put_obj_read(pd);
	return uobj_alloc_commit(uobj, attrs);

err_copy:
	uverbs_dealloc_mw(mw);
err_put:
	uobj_put_obj_read(pd);
err_free:
	uobj_alloc_abort(uobj, attrs);
	return ret;
}