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
typedef  union bnx2x_classification_ramrod_data {int dummy; } bnx2x_classification_ramrod_data ;
struct bnx2x_vlan_mac_registry_elem {int dummy; } ;
struct bnx2x_vlan_mac_obj {int (* check_add ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,union bnx2x_classification_ramrod_data*) ;struct bnx2x_vlan_mac_registry_elem* (* check_del ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,union bnx2x_classification_ramrod_data*) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 struct bnx2x_vlan_mac_registry_elem* stub1 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,union bnx2x_classification_ramrod_data*) ; 
 int stub2 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,union bnx2x_classification_ramrod_data*) ; 

__attribute__((used)) static bool bnx2x_check_move(struct bnx2x *bp,
			     struct bnx2x_vlan_mac_obj *src_o,
			     struct bnx2x_vlan_mac_obj *dst_o,
			     union bnx2x_classification_ramrod_data *data)
{
	struct bnx2x_vlan_mac_registry_elem *pos;
	int rc;

	/* Check if we can delete the requested configuration from the first
	 * object.
	 */
	pos = src_o->check_del(bp, src_o, data);

	/*  check if configuration can be added */
	rc = dst_o->check_add(bp, dst_o, data);

	/* If this classification can not be added (is already set)
	 * or can't be deleted - return an error.
	 */
	if (rc || !pos)
		return false;

	return true;
}