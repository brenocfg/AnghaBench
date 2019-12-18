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
struct ice_vsi {struct ice_port_info* port_info; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int link_info; } ;
struct TYPE_4__ {TYPE_1__ link_info; } ;
struct ice_port_info {TYPE_2__ phy; } ;
struct ice_pf {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ICE_AQ_MEDIA_AVAILABLE ; 
 int /*<<< orphan*/  ICE_FLAG_NO_MEDIA ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_force_phys_link_state (struct ice_vsi*,int) ; 
 struct ice_vsi* ice_get_main_vsi (struct ice_pf*) ; 
 int ice_update_link_info (struct ice_port_info*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_check_media_subtask(struct ice_pf *pf)
{
	struct ice_port_info *pi;
	struct ice_vsi *vsi;
	int err;

	vsi = ice_get_main_vsi(pf);
	if (!vsi)
		return;

	/* No need to check for media if it's already present or the interface
	 * is down
	 */
	if (!test_bit(ICE_FLAG_NO_MEDIA, pf->flags) ||
	    test_bit(__ICE_DOWN, vsi->state))
		return;

	/* Refresh link info and check if media is present */
	pi = vsi->port_info;
	err = ice_update_link_info(pi);
	if (err)
		return;

	if (pi->phy.link_info.link_info & ICE_AQ_MEDIA_AVAILABLE) {
		err = ice_force_phys_link_state(vsi, true);
		if (err)
			return;
		clear_bit(ICE_FLAG_NO_MEDIA, pf->flags);

		/* A Link Status Event will be generated; the event handler
		 * will complete bringing the interface up
		 */
	}
}