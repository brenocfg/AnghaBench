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
struct radeon_connector {int use_digital; } ;
struct drm_connector {scalar_t__ force; } ;

/* Variables and functions */
 scalar_t__ DRM_FORCE_ON ; 
 scalar_t__ DRM_FORCE_ON_DIGITAL ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static void radeon_dvi_force(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	if (connector->force == DRM_FORCE_ON)
		radeon_connector->use_digital = false;
	if (connector->force == DRM_FORCE_ON_DIGITAL)
		radeon_connector->use_digital = true;
}