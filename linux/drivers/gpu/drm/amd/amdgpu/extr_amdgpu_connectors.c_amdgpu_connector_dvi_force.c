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
struct drm_connector {scalar_t__ force; } ;
struct amdgpu_connector {int use_digital; } ;

/* Variables and functions */
 scalar_t__ DRM_FORCE_ON ; 
 scalar_t__ DRM_FORCE_ON_DIGITAL ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 

__attribute__((used)) static void amdgpu_connector_dvi_force(struct drm_connector *connector)
{
	struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	if (connector->force == DRM_FORCE_ON)
		amdgpu_connector->use_digital = false;
	if (connector->force == DRM_FORCE_ON_DIGITAL)
		amdgpu_connector->use_digital = true;
}