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
struct drm_display_mode {int hdisplay; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int MODE_ERROR ; 
 int MODE_OK ; 

__attribute__((used)) static int fsl_dcu_drm_connector_mode_valid(struct drm_connector *connector,
					    struct drm_display_mode *mode)
{
	if (mode->hdisplay & 0xf)
		return MODE_ERROR;

	return MODE_OK;
}