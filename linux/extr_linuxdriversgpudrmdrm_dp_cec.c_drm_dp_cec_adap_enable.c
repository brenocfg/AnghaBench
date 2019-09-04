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
typedef  int /*<<< orphan*/  u32 ;
struct drm_dp_aux {int dummy; } ;
struct cec_adapter {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_CEC_TUNNELING_CONTROL ; 
 int /*<<< orphan*/  DP_CEC_TUNNELING_ENABLE ; 
 struct drm_dp_aux* cec_get_drvdata (struct cec_adapter*) ; 
 scalar_t__ drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct drm_dp_aux *aux = cec_get_drvdata(adap);
	u32 val = enable ? DP_CEC_TUNNELING_ENABLE : 0;
	ssize_t err = 0;

	err = drm_dp_dpcd_writeb(aux, DP_CEC_TUNNELING_CONTROL, val);
	return (enable && err < 0) ? err : 0;
}