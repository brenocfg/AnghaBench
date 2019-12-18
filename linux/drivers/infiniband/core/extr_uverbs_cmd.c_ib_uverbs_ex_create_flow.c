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
union ib_flow_spec {scalar_t__ size; } ;
struct uverbs_req_iter {int dummy; } ;
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; } ;
struct ib_uverbs_flow_spec_hdr {int size; } ;
struct ib_uverbs_flow_spec {int dummy; } ;
struct ib_uverbs_flow_attr {int flags; scalar_t__ type; int num_of_specs; int size; struct ib_uverbs_flow_spec_hdr* flow_specs; int /*<<< orphan*/  port; int /*<<< orphan*/  priority; scalar_t__* reserved; } ;
struct ib_uverbs_create_flow_resp {int /*<<< orphan*/  flow_handle; } ;
struct ib_uverbs_create_flow {struct ib_uverbs_flow_attr flow_attr; int /*<<< orphan*/  qp_handle; scalar_t__ comp_mask; } ;
struct ib_uobject {int /*<<< orphan*/  id; } ;
struct ib_uflow_resources {int dummy; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  usecnt; TYPE_2__* device; } ;
struct ib_flow_attr {int flags; scalar_t__ type; int num_of_specs; int size; struct ib_uverbs_flow_spec_hdr* flow_specs; int /*<<< orphan*/  port; int /*<<< orphan*/  priority; scalar_t__* reserved; } ;
struct ib_flow {int /*<<< orphan*/  id; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy_flow ) (struct ib_uobject*) ;struct ib_uobject* (* create_flow ) (struct ib_qp*,struct ib_uverbs_flow_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_FLOW_ATTR_ALL_DEFAULT ; 
 int IB_FLOW_ATTR_FLAGS_DONT_TRAP ; 
 int IB_FLOW_ATTR_FLAGS_RESERVED ; 
 scalar_t__ IB_FLOW_ATTR_MC_DEFAULT ; 
 int /*<<< orphan*/  IB_FLOW_DOMAIN_USER ; 
 int IB_FLOW_SPEC_SUPPORT_LAYERS ; 
 scalar_t__ IB_QPT_RAW_PACKET ; 
 scalar_t__ IB_QPT_UD ; 
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int PTR_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  UVERBS_OBJECT_FLOW ; 
 int /*<<< orphan*/  UVERBS_OBJECT_QP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct ib_uflow_resources* flow_resources_alloc (int) ; 
 int /*<<< orphan*/  flows ; 
 int /*<<< orphan*/  ib_set_flow (struct ib_uobject*,struct ib_uobject*,struct ib_qp*,TYPE_2__*,struct ib_uflow_resources*) ; 
 int /*<<< orphan*/  ib_uverbs_flow_resources_free (struct ib_uflow_resources*) ; 
 int kern_spec_to_ib_spec (struct uverbs_attr_bundle*,struct ib_uverbs_flow_spec*,void*,struct ib_uflow_resources*) ; 
 int /*<<< orphan*/  kfree (struct ib_uverbs_flow_attr*) ; 
 struct ib_uverbs_flow_attr* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_uverbs_flow_attr* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_uverbs_create_flow_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int /*<<< orphan*/  struct_size (struct ib_uverbs_flow_attr*,int /*<<< orphan*/ ,int) ; 
 struct ib_uobject* stub1 (struct ib_qp*,struct ib_uverbs_flow_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ib_uobject*) ; 
 struct ib_uobject* uobj_alloc (int /*<<< orphan*/ ,struct uverbs_attr_bundle*,struct ib_device**) ; 
 int /*<<< orphan*/  uobj_alloc_abort (struct ib_uobject*,struct uverbs_attr_bundle*) ; 
 int uobj_alloc_commit (struct ib_uobject*,struct uverbs_attr_bundle*) ; 
 struct ib_qp* uobj_get_obj_read (struct ib_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_qp*) ; 
 int uverbs_request_finish (struct uverbs_req_iter*) ; 
 int uverbs_request_next (struct uverbs_req_iter*,struct ib_uverbs_flow_spec_hdr**,int) ; 
 int uverbs_request_start (struct uverbs_attr_bundle*,struct uverbs_req_iter*,struct ib_uverbs_create_flow*,int) ; 
 int uverbs_response (struct uverbs_attr_bundle*,struct ib_uverbs_create_flow_resp*,int) ; 

__attribute__((used)) static int ib_uverbs_ex_create_flow(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_create_flow	  cmd;
	struct ib_uverbs_create_flow_resp resp;
	struct ib_uobject		  *uobj;
	struct ib_flow			  *flow_id;
	struct ib_uverbs_flow_attr	  *kern_flow_attr;
	struct ib_flow_attr		  *flow_attr;
	struct ib_qp			  *qp;
	struct ib_uflow_resources	  *uflow_res;
	struct ib_uverbs_flow_spec_hdr	  *kern_spec;
	struct uverbs_req_iter iter;
	int err;
	void *ib_spec;
	int i;
	struct ib_device *ib_dev;

	err = uverbs_request_start(attrs, &iter, &cmd, sizeof(cmd));
	if (err)
		return err;

	if (cmd.comp_mask)
		return -EINVAL;

	if (!capable(CAP_NET_RAW))
		return -EPERM;

	if (cmd.flow_attr.flags >= IB_FLOW_ATTR_FLAGS_RESERVED)
		return -EINVAL;

	if ((cmd.flow_attr.flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP) &&
	    ((cmd.flow_attr.type == IB_FLOW_ATTR_ALL_DEFAULT) ||
	     (cmd.flow_attr.type == IB_FLOW_ATTR_MC_DEFAULT)))
		return -EINVAL;

	if (cmd.flow_attr.num_of_specs > IB_FLOW_SPEC_SUPPORT_LAYERS)
		return -EINVAL;

	if (cmd.flow_attr.size >
	    (cmd.flow_attr.num_of_specs * sizeof(struct ib_uverbs_flow_spec)))
		return -EINVAL;

	if (cmd.flow_attr.reserved[0] ||
	    cmd.flow_attr.reserved[1])
		return -EINVAL;

	if (cmd.flow_attr.num_of_specs) {
		kern_flow_attr = kmalloc(sizeof(*kern_flow_attr) + cmd.flow_attr.size,
					 GFP_KERNEL);
		if (!kern_flow_attr)
			return -ENOMEM;

		*kern_flow_attr = cmd.flow_attr;
		err = uverbs_request_next(&iter, &kern_flow_attr->flow_specs,
					  cmd.flow_attr.size);
		if (err)
			goto err_free_attr;
	} else {
		kern_flow_attr = &cmd.flow_attr;
	}

	err = uverbs_request_finish(&iter);
	if (err)
		goto err_free_attr;

	uobj = uobj_alloc(UVERBS_OBJECT_FLOW, attrs, &ib_dev);
	if (IS_ERR(uobj)) {
		err = PTR_ERR(uobj);
		goto err_free_attr;
	}

	qp = uobj_get_obj_read(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	if (!qp) {
		err = -EINVAL;
		goto err_uobj;
	}

	if (qp->qp_type != IB_QPT_UD && qp->qp_type != IB_QPT_RAW_PACKET) {
		err = -EINVAL;
		goto err_put;
	}

	flow_attr = kzalloc(struct_size(flow_attr, flows,
				cmd.flow_attr.num_of_specs), GFP_KERNEL);
	if (!flow_attr) {
		err = -ENOMEM;
		goto err_put;
	}
	uflow_res = flow_resources_alloc(cmd.flow_attr.num_of_specs);
	if (!uflow_res) {
		err = -ENOMEM;
		goto err_free_flow_attr;
	}

	flow_attr->type = kern_flow_attr->type;
	flow_attr->priority = kern_flow_attr->priority;
	flow_attr->num_of_specs = kern_flow_attr->num_of_specs;
	flow_attr->port = kern_flow_attr->port;
	flow_attr->flags = kern_flow_attr->flags;
	flow_attr->size = sizeof(*flow_attr);

	kern_spec = kern_flow_attr->flow_specs;
	ib_spec = flow_attr + 1;
	for (i = 0; i < flow_attr->num_of_specs &&
			cmd.flow_attr.size >= sizeof(*kern_spec) &&
			cmd.flow_attr.size >= kern_spec->size;
	     i++) {
		err = kern_spec_to_ib_spec(
				attrs, (struct ib_uverbs_flow_spec *)kern_spec,
				ib_spec, uflow_res);
		if (err)
			goto err_free;

		flow_attr->size +=
			((union ib_flow_spec *) ib_spec)->size;
		cmd.flow_attr.size -= kern_spec->size;
		kern_spec = ((void *)kern_spec) + kern_spec->size;
		ib_spec += ((union ib_flow_spec *) ib_spec)->size;
	}
	if (cmd.flow_attr.size || (i != flow_attr->num_of_specs)) {
		pr_warn("create flow failed, flow %d: %d bytes left from uverb cmd\n",
			i, cmd.flow_attr.size);
		err = -EINVAL;
		goto err_free;
	}

	flow_id = qp->device->ops.create_flow(
		qp, flow_attr, IB_FLOW_DOMAIN_USER, &attrs->driver_udata);

	if (IS_ERR(flow_id)) {
		err = PTR_ERR(flow_id);
		goto err_free;
	}

	ib_set_flow(uobj, flow_id, qp, qp->device, uflow_res);

	memset(&resp, 0, sizeof(resp));
	resp.flow_handle = uobj->id;

	err = uverbs_response(attrs, &resp, sizeof(resp));
	if (err)
		goto err_copy;

	uobj_put_obj_read(qp);
	kfree(flow_attr);
	if (cmd.flow_attr.num_of_specs)
		kfree(kern_flow_attr);
	return uobj_alloc_commit(uobj, attrs);
err_copy:
	if (!qp->device->ops.destroy_flow(flow_id))
		atomic_dec(&qp->usecnt);
err_free:
	ib_uverbs_flow_resources_free(uflow_res);
err_free_flow_attr:
	kfree(flow_attr);
err_put:
	uobj_put_obj_read(qp);
err_uobj:
	uobj_alloc_abort(uobj, attrs);
err_free_attr:
	if (cmd.flow_attr.num_of_specs)
		kfree(kern_flow_attr);
	return err;
}