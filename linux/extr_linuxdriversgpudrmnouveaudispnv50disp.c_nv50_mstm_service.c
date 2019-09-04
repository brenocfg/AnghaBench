#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {struct drm_dp_aux* aux; } ;
struct nv50_mstm {TYPE_1__ mgr; } ;
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_SINK_COUNT_ESI ; 
 int drm_dp_dpcd_read (struct drm_dp_aux*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_dp_dpcd_write (struct drm_dp_aux*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_dp_mst_hpd_irq (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_set_mst (TYPE_1__*,int) ; 

void
nv50_mstm_service(struct nv50_mstm *mstm)
{
	struct drm_dp_aux *aux = mstm ? mstm->mgr.aux : NULL;
	bool handled = true;
	int ret;
	u8 esi[8] = {};

	if (!aux)
		return;

	while (handled) {
		ret = drm_dp_dpcd_read(aux, DP_SINK_COUNT_ESI, esi, 8);
		if (ret != 8) {
			drm_dp_mst_topology_mgr_set_mst(&mstm->mgr, false);
			return;
		}

		drm_dp_mst_hpd_irq(&mstm->mgr, esi, &handled);
		if (!handled)
			break;

		drm_dp_dpcd_write(aux, DP_SINK_COUNT_ESI + 1, &esi[1], 3);
	}
}