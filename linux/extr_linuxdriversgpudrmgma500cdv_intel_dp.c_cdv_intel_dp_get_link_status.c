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
struct gma_encoder {struct cdv_intel_dp* dev_priv; } ;
struct cdv_intel_dp {int /*<<< orphan*/  link_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LANE0_1_STATUS ; 
 int /*<<< orphan*/  DP_LINK_STATUS_SIZE ; 
 int cdv_intel_dp_aux_native_read_retry (struct gma_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cdv_intel_dp_get_link_status(struct gma_encoder *encoder)
{
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	return cdv_intel_dp_aux_native_read_retry(encoder,
					      DP_LANE0_1_STATUS,
					      intel_dp->link_status,
					      DP_LINK_STATUS_SIZE);
}