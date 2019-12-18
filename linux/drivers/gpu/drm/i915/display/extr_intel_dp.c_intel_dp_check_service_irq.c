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
typedef  int u8 ;
struct intel_dp {int* dpcd; int /*<<< orphan*/  attached_connector; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int DP_AUTOMATED_TEST_REQUEST ; 
 int DP_CP_IRQ ; 
 int /*<<< orphan*/  DP_DEVICE_SERVICE_IRQ_VECTOR ; 
 size_t DP_DPCD_REV ; 
 int DP_SINK_SPECIFIC_IRQ ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_dp_handle_test_request (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_hdcp_handle_cp_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_check_service_irq(struct intel_dp *intel_dp)
{
	u8 val;

	if (intel_dp->dpcd[DP_DPCD_REV] < 0x11)
		return;

	if (drm_dp_dpcd_readb(&intel_dp->aux,
			      DP_DEVICE_SERVICE_IRQ_VECTOR, &val) != 1 || !val)
		return;

	drm_dp_dpcd_writeb(&intel_dp->aux, DP_DEVICE_SERVICE_IRQ_VECTOR, val);

	if (val & DP_AUTOMATED_TEST_REQUEST)
		intel_dp_handle_test_request(intel_dp);

	if (val & DP_CP_IRQ)
		intel_hdcp_handle_cp_irq(intel_dp->attached_connector);

	if (val & DP_SINK_SPECIFIC_IRQ)
		DRM_DEBUG_DRIVER("Sink specific irq unhandled\n");
}