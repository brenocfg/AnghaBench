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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dc_link {struct amdgpu_dm_connector* priv; } ;
struct dc_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;
struct amdgpu_dm_connector {TYPE_1__ dm_dp_aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ drm_dp_dpcd_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool dm_helpers_dp_write_dpcd(
		struct dc_context *ctx,
		const struct dc_link *link,
		uint32_t address,
		const uint8_t *data,
		uint32_t size)
{
	struct amdgpu_dm_connector *aconnector = link->priv;

	if (!aconnector) {
		DRM_ERROR("Failed to found connector for link!");
		return false;
	}

	return drm_dp_dpcd_write(&aconnector->dm_dp_aux.aux,
			address, (uint8_t *)data, size) > 0;
}