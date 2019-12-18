#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int size; void* counters; } ;
struct TYPE_14__ {int size; void* act; } ;
struct TYPE_12__ {int size; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  tag_id; } ;
union ib_flow_spec {int type; TYPE_8__ flow_count; TYPE_6__ action; TYPE_4__ drop; TYPE_1__ flow_tag; } ;
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uverbs_flow_spec_action_tag {int dummy; } ;
struct ib_uverbs_flow_spec_action_handle {int dummy; } ;
struct ib_uverbs_flow_spec_action_drop {int dummy; } ;
struct ib_uverbs_flow_spec_action_count {int dummy; } ;
struct TYPE_15__ {int size; int /*<<< orphan*/  handle; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/  handle; } ;
struct TYPE_11__ {int size; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  tag_id; } ;
struct ib_uverbs_flow_spec {int type; TYPE_7__ flow_count; TYPE_5__ action; TYPE_3__ drop; TYPE_2__ flow_tag; } ;
struct ib_uflow_resources {int dummy; } ;
struct ib_flow_spec_action_tag {int dummy; } ;
struct ib_flow_spec_action_handle {int dummy; } ;
struct ib_flow_spec_action_drop {int dummy; } ;
struct ib_flow_spec_action_count {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IB_FLOW_SPEC_ACTION_COUNT 131 
#define  IB_FLOW_SPEC_ACTION_DROP 130 
#define  IB_FLOW_SPEC_ACTION_HANDLE 129 
#define  IB_FLOW_SPEC_ACTION_TAG 128 
 int /*<<< orphan*/  UVERBS_OBJECT_COUNTERS ; 
 int /*<<< orphan*/  UVERBS_OBJECT_FLOW_ACTION ; 
 int /*<<< orphan*/  counters ; 
 int /*<<< orphan*/  flow_action ; 
 int /*<<< orphan*/  flow_resources_add (struct ib_uflow_resources*,int const,void*) ; 
 void* uobj_get_obj_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (void*) ; 

__attribute__((used)) static int kern_spec_to_ib_spec_action(struct uverbs_attr_bundle *attrs,
				       struct ib_uverbs_flow_spec *kern_spec,
				       union ib_flow_spec *ib_spec,
				       struct ib_uflow_resources *uflow_res)
{
	ib_spec->type = kern_spec->type;
	switch (ib_spec->type) {
	case IB_FLOW_SPEC_ACTION_TAG:
		if (kern_spec->flow_tag.size !=
		    sizeof(struct ib_uverbs_flow_spec_action_tag))
			return -EINVAL;

		ib_spec->flow_tag.size = sizeof(struct ib_flow_spec_action_tag);
		ib_spec->flow_tag.tag_id = kern_spec->flow_tag.tag_id;
		break;
	case IB_FLOW_SPEC_ACTION_DROP:
		if (kern_spec->drop.size !=
		    sizeof(struct ib_uverbs_flow_spec_action_drop))
			return -EINVAL;

		ib_spec->drop.size = sizeof(struct ib_flow_spec_action_drop);
		break;
	case IB_FLOW_SPEC_ACTION_HANDLE:
		if (kern_spec->action.size !=
		    sizeof(struct ib_uverbs_flow_spec_action_handle))
			return -EOPNOTSUPP;
		ib_spec->action.act = uobj_get_obj_read(flow_action,
							UVERBS_OBJECT_FLOW_ACTION,
							kern_spec->action.handle,
							attrs);
		if (!ib_spec->action.act)
			return -EINVAL;
		ib_spec->action.size =
			sizeof(struct ib_flow_spec_action_handle);
		flow_resources_add(uflow_res,
				   IB_FLOW_SPEC_ACTION_HANDLE,
				   ib_spec->action.act);
		uobj_put_obj_read(ib_spec->action.act);
		break;
	case IB_FLOW_SPEC_ACTION_COUNT:
		if (kern_spec->flow_count.size !=
			sizeof(struct ib_uverbs_flow_spec_action_count))
			return -EINVAL;
		ib_spec->flow_count.counters =
			uobj_get_obj_read(counters,
					  UVERBS_OBJECT_COUNTERS,
					  kern_spec->flow_count.handle,
					  attrs);
		if (!ib_spec->flow_count.counters)
			return -EINVAL;
		ib_spec->flow_count.size =
				sizeof(struct ib_flow_spec_action_count);
		flow_resources_add(uflow_res,
				   IB_FLOW_SPEC_ACTION_COUNT,
				   ib_spec->flow_count.counters);
		uobj_put_obj_read(ib_spec->flow_count.counters);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}