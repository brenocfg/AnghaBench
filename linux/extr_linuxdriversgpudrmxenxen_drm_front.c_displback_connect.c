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
struct xen_drm_front_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNL_STATE_CONNECTED ; 
 int xen_drm_drv_init (struct xen_drm_front_info*) ; 
 int /*<<< orphan*/  xen_drm_front_evtchnl_set_state (struct xen_drm_front_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int displback_connect(struct xen_drm_front_info *front_info)
{
	xen_drm_front_evtchnl_set_state(front_info, EVTCHNL_STATE_CONNECTED);
	return xen_drm_drv_init(front_info);
}