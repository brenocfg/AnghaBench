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
typedef  int /*<<< orphan*/  u8 ;
struct drm_dp_aux {int dummy; } ;
struct cec_adapter {int capabilities; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int CEC_CAP_MONITOR_ALL ; 
 int /*<<< orphan*/  DP_CEC_SNOOPING_ENABLE ; 
 int /*<<< orphan*/  DP_CEC_TUNNELING_CONTROL ; 
 struct drm_dp_aux* cec_get_drvdata (struct cec_adapter*) ; 
 scalar_t__ drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_cec_adap_monitor_all_enable(struct cec_adapter *adap,
					      bool enable)
{
	struct drm_dp_aux *aux = cec_get_drvdata(adap);
	ssize_t err;
	u8 val;

	if (!(adap->capabilities & CEC_CAP_MONITOR_ALL))
		return 0;

	err = drm_dp_dpcd_readb(aux, DP_CEC_TUNNELING_CONTROL, &val);
	if (err >= 0) {
		if (enable)
			val |= DP_CEC_SNOOPING_ENABLE;
		else
			val &= ~DP_CEC_SNOOPING_ENABLE;
		err = drm_dp_dpcd_writeb(aux, DP_CEC_TUNNELING_CONTROL, val);
	}
	return (enable && err < 0) ? err : 0;
}