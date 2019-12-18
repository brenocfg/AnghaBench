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
struct xen_drm_front_cfg {int /*<<< orphan*/  num_connectors; struct xen_drm_front_info* front_info; } ;
struct xen_drm_front_info {struct xen_drm_front_cfg cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int xen_drm_front_cfg_card (struct xen_drm_front_info*,struct xen_drm_front_cfg*) ; 
 int xen_drm_front_evtchnl_create_all (struct xen_drm_front_info*) ; 
 int xen_drm_front_evtchnl_publish_all (struct xen_drm_front_info*) ; 

__attribute__((used)) static int displback_initwait(struct xen_drm_front_info *front_info)
{
	struct xen_drm_front_cfg *cfg = &front_info->cfg;
	int ret;

	cfg->front_info = front_info;
	ret = xen_drm_front_cfg_card(front_info, cfg);
	if (ret < 0)
		return ret;

	DRM_INFO("Have %d connector(s)\n", cfg->num_connectors);
	/* Create event channels for all connectors and publish */
	ret = xen_drm_front_evtchnl_create_all(front_info);
	if (ret < 0)
		return ret;

	return xen_drm_front_evtchnl_publish_all(front_info);
}