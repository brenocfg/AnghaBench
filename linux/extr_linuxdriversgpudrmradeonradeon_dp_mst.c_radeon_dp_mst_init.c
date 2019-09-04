#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ base; struct drm_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * cbs; } ;
struct radeon_connector {TYPE_2__ base; TYPE_3__* ddc_bus; TYPE_4__ mst_mgr; } ;
struct drm_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  aux; int /*<<< orphan*/  has_aux; } ;

/* Variables and functions */
 int drm_dp_mst_topology_mgr_init (TYPE_4__*,struct drm_device*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mst_cbs ; 

int
radeon_dp_mst_init(struct radeon_connector *radeon_connector)
{
	struct drm_device *dev = radeon_connector->base.dev;

	if (!radeon_connector->ddc_bus->has_aux)
		return 0;

	radeon_connector->mst_mgr.cbs = &mst_cbs;
	return drm_dp_mst_topology_mgr_init(&radeon_connector->mst_mgr, dev,
					    &radeon_connector->ddc_bus->aux, 16, 6,
					    radeon_connector->base.base.id);
}