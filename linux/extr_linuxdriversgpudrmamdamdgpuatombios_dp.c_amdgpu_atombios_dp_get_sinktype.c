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
typedef  int /*<<< orphan*/  u8 ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct amdgpu_connector {TYPE_3__* ddc_bus; TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_id; } ;
struct TYPE_6__ {TYPE_2__ rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DP_ACTION_GET_SINK_TYPE ; 
 int /*<<< orphan*/  amdgpu_atombios_dp_encoder_service (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 amdgpu_atombios_dp_get_sinktype(struct amdgpu_connector *amdgpu_connector)
{
	struct drm_device *dev = amdgpu_connector->base.dev;
	struct amdgpu_device *adev = dev->dev_private;

	return amdgpu_atombios_dp_encoder_service(adev, ATOM_DP_ACTION_GET_SINK_TYPE, 0,
					   amdgpu_connector->ddc_bus->rec.i2c_id, 0);
}