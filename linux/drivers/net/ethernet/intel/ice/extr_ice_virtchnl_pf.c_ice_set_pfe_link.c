#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int link_status; int link_speed; } ;
struct TYPE_4__ {int link_status; scalar_t__ link_speed; } ;
struct TYPE_5__ {TYPE_3__ link_event; TYPE_1__ link_event_adv; } ;
struct virtchnl_pf_event {TYPE_2__ event_data; } ;
struct ice_vf {int driver_caps; } ;
typedef  enum virtchnl_link_speed { ____Placeholder_virtchnl_link_speed } virtchnl_link_speed ;

/* Variables and functions */
 int VIRTCHNL_VF_CAP_ADV_LINK_SPEED ; 
 scalar_t__ ice_conv_link_speed_to_virtchnl (int,int) ; 

__attribute__((used)) static void
ice_set_pfe_link(struct ice_vf *vf, struct virtchnl_pf_event *pfe,
		 int ice_link_speed, bool link_up)
{
	if (vf->driver_caps & VIRTCHNL_VF_CAP_ADV_LINK_SPEED) {
		pfe->event_data.link_event_adv.link_status = link_up;
		/* Speed in Mbps */
		pfe->event_data.link_event_adv.link_speed =
			ice_conv_link_speed_to_virtchnl(true, ice_link_speed);
	} else {
		pfe->event_data.link_event.link_status = link_up;
		/* Legacy method for virtchnl link speeds */
		pfe->event_data.link_event.link_speed =
			(enum virtchnl_link_speed)
			ice_conv_link_speed_to_virtchnl(false, ice_link_speed);
	}
}