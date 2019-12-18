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
typedef  int /*<<< orphan*/  u32 ;
struct xen_drm_front_drm_pipeline {int index; int /*<<< orphan*/  conn; int /*<<< orphan*/  pipe; int /*<<< orphan*/  pflip_to_worker; int /*<<< orphan*/  width; int /*<<< orphan*/  height; struct xen_drm_front_drm_info* drm_info; } ;
struct xen_drm_front_drm_info {struct drm_device* drm_dev; } ;
struct xen_drm_front_cfg_connector {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_funcs ; 
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pflip_to_worker ; 
 int /*<<< orphan*/ * xen_drm_front_conn_get_formats (int*) ; 
 int xen_drm_front_conn_init (struct xen_drm_front_drm_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int display_pipe_init(struct xen_drm_front_drm_info *drm_info,
			     int index, struct xen_drm_front_cfg_connector *cfg,
			     struct xen_drm_front_drm_pipeline *pipeline)
{
	struct drm_device *dev = drm_info->drm_dev;
	const u32 *formats;
	int format_count;
	int ret;

	pipeline->drm_info = drm_info;
	pipeline->index = index;
	pipeline->height = cfg->height;
	pipeline->width = cfg->width;

	INIT_DELAYED_WORK(&pipeline->pflip_to_worker, pflip_to_worker);

	ret = xen_drm_front_conn_init(drm_info, &pipeline->conn);
	if (ret)
		return ret;

	formats = xen_drm_front_conn_get_formats(&format_count);

	return drm_simple_display_pipe_init(dev, &pipeline->pipe,
					    &display_funcs, formats,
					    format_count, NULL,
					    &pipeline->conn);
}