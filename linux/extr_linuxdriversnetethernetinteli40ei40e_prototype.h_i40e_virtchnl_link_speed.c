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
typedef  enum virtchnl_link_speed { ____Placeholder_virtchnl_link_speed } virtchnl_link_speed ;
typedef  enum i40e_aq_link_speed { ____Placeholder_i40e_aq_link_speed } i40e_aq_link_speed ;

/* Variables and functions */
#define  I40E_LINK_SPEED_100MB 134 
#define  I40E_LINK_SPEED_10GB 133 
#define  I40E_LINK_SPEED_1GB 132 
#define  I40E_LINK_SPEED_20GB 131 
#define  I40E_LINK_SPEED_25GB 130 
#define  I40E_LINK_SPEED_40GB 129 
#define  I40E_LINK_SPEED_UNKNOWN 128 
 int VIRTCHNL_LINK_SPEED_100MB ; 
 int VIRTCHNL_LINK_SPEED_10GB ; 
 int VIRTCHNL_LINK_SPEED_1GB ; 
 int VIRTCHNL_LINK_SPEED_20GB ; 
 int VIRTCHNL_LINK_SPEED_25GB ; 
 int VIRTCHNL_LINK_SPEED_40GB ; 
 int VIRTCHNL_LINK_SPEED_UNKNOWN ; 

__attribute__((used)) static inline enum virtchnl_link_speed
i40e_virtchnl_link_speed(enum i40e_aq_link_speed link_speed)
{
	switch (link_speed) {
	case I40E_LINK_SPEED_100MB:
		return VIRTCHNL_LINK_SPEED_100MB;
	case I40E_LINK_SPEED_1GB:
		return VIRTCHNL_LINK_SPEED_1GB;
	case I40E_LINK_SPEED_10GB:
		return VIRTCHNL_LINK_SPEED_10GB;
	case I40E_LINK_SPEED_40GB:
		return VIRTCHNL_LINK_SPEED_40GB;
	case I40E_LINK_SPEED_20GB:
		return VIRTCHNL_LINK_SPEED_20GB;
	case I40E_LINK_SPEED_25GB:
		return VIRTCHNL_LINK_SPEED_25GB;
	case I40E_LINK_SPEED_UNKNOWN:
	default:
		return VIRTCHNL_LINK_SPEED_UNKNOWN;
	}
}