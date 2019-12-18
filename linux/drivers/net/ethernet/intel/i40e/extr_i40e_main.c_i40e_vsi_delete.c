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
struct i40e_vsi {int /*<<< orphan*/  seid; TYPE_1__* back; } ;
struct TYPE_2__ {size_t lan_vsi; int /*<<< orphan*/  hw; struct i40e_vsi** vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_aq_delete_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_vsi_delete(struct i40e_vsi *vsi)
{
	/* remove default VSI is not allowed */
	if (vsi == vsi->back->vsi[vsi->back->lan_vsi])
		return;

	i40e_aq_delete_element(&vsi->back->hw, vsi->seid, NULL);
}