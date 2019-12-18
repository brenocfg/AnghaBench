#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i40e_vsi {size_t veb_idx; struct i40e_pf* back; } ;
struct i40e_veb {int bridge_mode; } ;
struct i40e_pf {TYPE_1__* pdev; struct i40e_veb** veb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRIDGE_MODE_VEPA ; 
 int ENOENT ; 
 size_t I40E_MAX_VEB ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

int i40e_is_vsi_uplink_mode_veb(struct i40e_vsi *vsi)
{
	struct i40e_veb *veb;
	struct i40e_pf *pf = vsi->back;

	/* Uplink is not a bridge so default to VEB */
	if (vsi->veb_idx >= I40E_MAX_VEB)
		return 1;

	veb = pf->veb[vsi->veb_idx];
	if (!veb) {
		dev_info(&pf->pdev->dev,
			 "There is no veb associated with the bridge\n");
		return -ENOENT;
	}

	/* Uplink is a bridge in VEPA mode */
	if (veb->bridge_mode & BRIDGE_MODE_VEPA) {
		return 0;
	} else {
		/* Uplink is a bridge in VEB mode */
		return 1;
	}

	/* VEPA is now default bridge, so return 0 */
	return 0;
}