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
struct TYPE_4__ {scalar_t__ supported; } ;
struct TYPE_5__ {TYPE_1__ scdc; } ;
struct TYPE_6__ {int color_formats; TYPE_2__ hdmi; } ;
struct drm_connector {TYPE_3__ display_info; } ;

/* Variables and functions */
 int DRM_COLOR_FORMAT_YCRCB420 ; 

__attribute__((used)) static bool is_hdmi2_sink(struct drm_connector *connector)
{
	/*
	 * FIXME: sil-sii8620 doesn't have a connector around when
	 * we need one, so we have to be prepared for a NULL connector.
	 */
	if (!connector)
		return true;

	return connector->display_info.hdmi.scdc.supported ||
		connector->display_info.color_formats & DRM_COLOR_FORMAT_YCRCB420;
}