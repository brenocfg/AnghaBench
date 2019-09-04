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
typedef  int /*<<< orphan*/  u16 ;
struct ice_sched_vsi_info {int /*<<< orphan*/  vsi_id; int /*<<< orphan*/  list_entry; } ;
struct ice_port_info {int /*<<< orphan*/  vsi_info_list; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ice_sched_vsi_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ice_sched_vsi_info *
ice_sched_create_vsi_info_entry(struct ice_port_info *pi, u16 vsi_id)
{
	struct ice_sched_vsi_info *vsi_elem;

	if (!pi)
		return NULL;

	vsi_elem = devm_kzalloc(ice_hw_to_dev(pi->hw), sizeof(*vsi_elem),
				GFP_KERNEL);
	if (!vsi_elem)
		return NULL;

	list_add(&vsi_elem->list_entry, &pi->vsi_info_list);
	vsi_elem->vsi_id = vsi_id;
	return vsi_elem;
}