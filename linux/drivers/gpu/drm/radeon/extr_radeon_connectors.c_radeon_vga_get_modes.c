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
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_connector_get_edid (struct drm_connector*) ; 
 int radeon_ddc_get_modes (struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_get_native_mode (struct drm_connector*) ; 

__attribute__((used)) static int radeon_vga_get_modes(struct drm_connector *connector)
{
	int ret;

	radeon_connector_get_edid(connector);
	ret = radeon_ddc_get_modes(connector);

	radeon_get_native_mode(connector);

	return ret;
}