#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct intel_lspcon {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_REV ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* lspcon_to_intel_dp (struct intel_lspcon*) ; 

__attribute__((used)) static bool lspcon_wake_native_aux_ch(struct intel_lspcon *lspcon)
{
	u8 rev;

	if (drm_dp_dpcd_readb(&lspcon_to_intel_dp(lspcon)->aux, DP_DPCD_REV,
			      &rev) != 1) {
		DRM_DEBUG_KMS("Native AUX CH down\n");
		return false;
	}

	DRM_DEBUG_KMS("Native AUX CH up, DPCD version: %d.%d\n",
		      rev >> 4, rev & 0xf);

	return true;
}