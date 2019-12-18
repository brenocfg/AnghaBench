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
typedef  int uint32_t ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int drm_helper_probe_single_connector_modes (struct drm_connector*,int,int) ; 

__attribute__((used)) static int
rk3066_hdmi_probe_single_connector_modes(struct drm_connector *connector,
					 uint32_t maxX, uint32_t maxY)
{
	if (maxX > 1920)
		maxX = 1920;
	if (maxY > 1080)
		maxY = 1080;

	return drm_helper_probe_single_connector_modes(connector, maxX, maxY);
}