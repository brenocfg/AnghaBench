#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct i40e_vsi {int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {scalar_t__ link_speed; } ;
struct TYPE_7__ {int link_info; scalar_t__ link_speed; } ;
struct TYPE_9__ {int get_link_info; TYPE_3__ link_info; TYPE_2__ link_info_old; } ;
struct TYPE_10__ {TYPE_4__ phy; } ;
struct i40e_pf {size_t lan_vsi; size_t lan_veb; int flags; scalar_t__ vf; scalar_t__* veb; TYPE_5__ hw; TYPE_1__* pdev; int /*<<< orphan*/  state; struct i40e_vsi** vsi; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I40E_AQ_LINK_UP ; 
 int I40E_FLAG_PTP ; 
 size_t I40E_MAX_VEB ; 
 scalar_t__ I40E_SUCCESS ; 
 int /*<<< orphan*/  __I40E_TEMP_LINK_POLLING ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ i40e_get_link_status (TYPE_5__*,int*) ; 
 int /*<<< orphan*/  i40e_print_link_message (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_ptp_set_increment (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_vc_notify_link_state (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_veb_link_event (scalar_t__,int) ; 
 int /*<<< orphan*/  i40e_vsi_link_event (struct i40e_vsi*,int) ; 
 int netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_link_event(struct i40e_pf *pf)
{
	struct i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	u8 new_link_speed, old_link_speed;
	i40e_status status;
	bool new_link, old_link;

	/* set this to force the get_link_status call to refresh state */
	pf->hw.phy.get_link_info = true;
	old_link = (pf->hw.phy.link_info_old.link_info & I40E_AQ_LINK_UP);
	status = i40e_get_link_status(&pf->hw, &new_link);

	/* On success, disable temp link polling */
	if (status == I40E_SUCCESS) {
		clear_bit(__I40E_TEMP_LINK_POLLING, pf->state);
	} else {
		/* Enable link polling temporarily until i40e_get_link_status
		 * returns I40E_SUCCESS
		 */
		set_bit(__I40E_TEMP_LINK_POLLING, pf->state);
		dev_dbg(&pf->pdev->dev, "couldn't get link state, status: %d\n",
			status);
		return;
	}

	old_link_speed = pf->hw.phy.link_info_old.link_speed;
	new_link_speed = pf->hw.phy.link_info.link_speed;

	if (new_link == old_link &&
	    new_link_speed == old_link_speed &&
	    (test_bit(__I40E_VSI_DOWN, vsi->state) ||
	     new_link == netif_carrier_ok(vsi->netdev)))
		return;

	i40e_print_link_message(vsi, new_link);

	/* Notify the base of the switch tree connected to
	 * the link.  Floating VEBs are not notified.
	 */
	if (pf->lan_veb < I40E_MAX_VEB && pf->veb[pf->lan_veb])
		i40e_veb_link_event(pf->veb[pf->lan_veb], new_link);
	else
		i40e_vsi_link_event(vsi, new_link);

	if (pf->vf)
		i40e_vc_notify_link_state(pf);

	if (pf->flags & I40E_FLAG_PTP)
		i40e_ptp_set_increment(pf);
}