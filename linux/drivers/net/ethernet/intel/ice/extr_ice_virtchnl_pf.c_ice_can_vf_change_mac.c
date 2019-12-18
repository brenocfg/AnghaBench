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
struct ice_vf {scalar_t__ pf_set_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_is_vf_trusted (struct ice_vf*) ; 

__attribute__((used)) static bool ice_can_vf_change_mac(struct ice_vf *vf)
{
	/* If the VF MAC address has been set administratively (via the
	 * ndo_set_vf_mac command), then deny permission to the VF to
	 * add/delete unicast MAC addresses, unless the VF is trusted
	 */
	if (vf->pf_set_mac && !ice_is_vf_trusted(vf))
		return false;

	return true;
}