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
 int /*<<< orphan*/  DP_DEVICE_SERVICE_IRQ_VECTOR ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
intel_dp_get_sink_irq(struct intel_dp *intel_dp, u8 *sink_irq_vector)
{
	return drm_dp_dpcd_readb(&intel_dp->aux, DP_DEVICE_SERVICE_IRQ_VECTOR,
				 sink_irq_vector) == 1;
}