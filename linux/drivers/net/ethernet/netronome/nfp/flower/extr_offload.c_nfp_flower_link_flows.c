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
struct TYPE_4__ {int /*<<< orphan*/  list; struct nfp_fl_payload* flow; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; struct nfp_fl_payload* flow; } ;
struct nfp_fl_payload_link {TYPE_2__ sub_flow; TYPE_1__ merge_flow; } ;
struct nfp_fl_payload {int /*<<< orphan*/  linked_flows; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfp_fl_payload_link* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfp_flower_link_flows(struct nfp_fl_payload *merge_flow,
				 struct nfp_fl_payload *sub_flow)
{
	struct nfp_fl_payload_link *link;

	link = kmalloc(sizeof(*link), GFP_KERNEL);
	if (!link)
		return -ENOMEM;

	link->merge_flow.flow = merge_flow;
	list_add_tail(&link->merge_flow.list, &merge_flow->linked_flows);
	link->sub_flow.flow = sub_flow;
	list_add_tail(&link->sub_flow.list, &sub_flow->linked_flows);

	return 0;
}