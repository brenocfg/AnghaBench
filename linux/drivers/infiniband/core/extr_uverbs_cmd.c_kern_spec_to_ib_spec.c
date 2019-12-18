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
typedef  union ib_flow_spec {int dummy; } ib_flow_spec ;
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uverbs_flow_spec {scalar_t__ type; scalar_t__ reserved; } ;
struct ib_uflow_resources {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_FLOW_SPEC_ACTION_TAG ; 
 int kern_spec_to_ib_spec_action (struct uverbs_attr_bundle*,struct ib_uverbs_flow_spec*,union ib_flow_spec*,struct ib_uflow_resources*) ; 
 int kern_spec_to_ib_spec_filter (struct ib_uverbs_flow_spec*,union ib_flow_spec*) ; 

__attribute__((used)) static int kern_spec_to_ib_spec(struct uverbs_attr_bundle *attrs,
				struct ib_uverbs_flow_spec *kern_spec,
				union ib_flow_spec *ib_spec,
				struct ib_uflow_resources *uflow_res)
{
	if (kern_spec->reserved)
		return -EINVAL;

	if (kern_spec->type >= IB_FLOW_SPEC_ACTION_TAG)
		return kern_spec_to_ib_spec_action(attrs, kern_spec, ib_spec,
						   uflow_res);
	else
		return kern_spec_to_ib_spec_filter(kern_spec, ib_spec);
}