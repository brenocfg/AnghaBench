#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  kdev; struct drm_device* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  hpd; } ;
struct radeon_connector {TYPE_4__* ddc_bus; TYPE_3__ base; TYPE_2__ hpd; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_10__ {void* transfer; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  hpd; } ;
struct TYPE_9__ {int has_aux; TYPE_5__ aux; TYPE_1__ rec; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int drm_dp_aux_register (TYPE_5__*) ; 
 scalar_t__ radeon_auxch ; 
 void* radeon_dp_aux_transfer_atom ; 
 void* radeon_dp_aux_transfer_native ; 

void radeon_dp_aux_init(struct radeon_connector *radeon_connector)
{
	struct drm_device *dev = radeon_connector->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	int ret;

	radeon_connector->ddc_bus->rec.hpd = radeon_connector->hpd.hpd;
	radeon_connector->ddc_bus->aux.dev = radeon_connector->base.kdev;
	if (ASIC_IS_DCE5(rdev)) {
		if (radeon_auxch)
			radeon_connector->ddc_bus->aux.transfer = radeon_dp_aux_transfer_native;
		else
			radeon_connector->ddc_bus->aux.transfer = radeon_dp_aux_transfer_atom;
	} else {
		radeon_connector->ddc_bus->aux.transfer = radeon_dp_aux_transfer_atom;
	}

	ret = drm_dp_aux_register(&radeon_connector->ddc_bus->aux);
	if (!ret)
		radeon_connector->ddc_bus->has_aux = true;

	WARN(ret, "drm_dp_aux_register() failed with error %d\n", ret);
}