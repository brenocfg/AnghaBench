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
struct intel_dp {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 scalar_t__ DP_DPRX_ESI_LEN ; 
 int /*<<< orphan*/  DP_SINK_COUNT_ESI ; 
 scalar_t__ drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool
intel_dp_get_sink_irq_esi(struct intel_dp *intel_dp, u8 *sink_irq_vector)
{
	return drm_dp_dpcd_read(&intel_dp->aux, DP_SINK_COUNT_ESI,
				sink_irq_vector, DP_DPRX_ESI_LEN) ==
		DP_DPRX_ESI_LEN;
}