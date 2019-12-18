#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_connector {int dummy; } ;
struct amdgpu_connector {TYPE_1__* ddc_bus; } ;
struct TYPE_2__ {int has_aux; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_aux_unregister (int /*<<< orphan*/ *) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 

__attribute__((used)) static void amdgpu_connector_unregister(struct drm_connector *connector)
{
	struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	if (amdgpu_connector->ddc_bus && amdgpu_connector->ddc_bus->has_aux) {
		drm_dp_aux_unregister(&amdgpu_connector->ddc_bus->aux);
		amdgpu_connector->ddc_bus->has_aux = false;
	}
}