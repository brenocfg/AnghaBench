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
typedef  int /*<<< orphan*/  u8 ;
struct ice_vsi {TYPE_2__* back; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int ice_add_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ice_add_mac_to_list (struct ice_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_remove_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_add_list ; 

enum ice_status
ice_vsi_cfg_mac_fltr(struct ice_vsi *vsi, const u8 *macaddr, bool set)
{
	LIST_HEAD(tmp_add_list);
	enum ice_status status;

	 /* Update MAC filter list to be added or removed for a VSI */
	if (ice_add_mac_to_list(vsi, &tmp_add_list, macaddr)) {
		status = ICE_ERR_NO_MEMORY;
		goto cfg_mac_fltr_exit;
	}

	if (set)
		status = ice_add_mac(&vsi->back->hw, &tmp_add_list);
	else
		status = ice_remove_mac(&vsi->back->hw, &tmp_add_list);

cfg_mac_fltr_exit:
	ice_free_fltr_list(&vsi->back->pdev->dev, &tmp_add_list);
	return status;
}