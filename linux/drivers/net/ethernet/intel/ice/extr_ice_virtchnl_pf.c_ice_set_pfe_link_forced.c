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
struct virtchnl_pf_event {int dummy; } ;
struct ice_vf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_LINK_SPEED_100GB ; 
 int /*<<< orphan*/  ICE_AQ_LINK_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ice_set_pfe_link (struct ice_vf*,struct virtchnl_pf_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ice_set_pfe_link_forced(struct ice_vf *vf, struct virtchnl_pf_event *pfe,
			bool link_up)
{
	u16 link_speed;

	if (link_up)
		link_speed = ICE_AQ_LINK_SPEED_100GB;
	else
		link_speed = ICE_AQ_LINK_SPEED_UNKNOWN;

	ice_set_pfe_link(vf, pfe, link_speed, link_up);
}