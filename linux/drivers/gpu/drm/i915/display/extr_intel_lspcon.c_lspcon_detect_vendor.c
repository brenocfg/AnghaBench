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
typedef  int u32 ;
struct intel_lspcon {int /*<<< orphan*/  vendor; } ;
struct drm_dp_dpcd_ident {int* oui; } ;
struct TYPE_2__ {struct drm_dp_dpcd_ident ident; } ;
struct intel_dp {TYPE_1__ desc; int /*<<< orphan*/  dpcd; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  LSPCON_VENDOR_MCA ; 
#define  LSPCON_VENDOR_MCA_OUI 129 
 int /*<<< orphan*/  LSPCON_VENDOR_PARADE ; 
#define  LSPCON_VENDOR_PARADE_OUI 128 
 int /*<<< orphan*/  drm_dp_is_branch (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dp_read_desc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct intel_dp* lspcon_to_intel_dp (struct intel_lspcon*) ; 

__attribute__((used)) static bool lspcon_detect_vendor(struct intel_lspcon *lspcon)
{
	struct intel_dp *dp = lspcon_to_intel_dp(lspcon);
	struct drm_dp_dpcd_ident *ident;
	u32 vendor_oui;

	if (drm_dp_read_desc(&dp->aux, &dp->desc, drm_dp_is_branch(dp->dpcd))) {
		DRM_ERROR("Can't read description\n");
		return false;
	}

	ident = &dp->desc.ident;
	vendor_oui = (ident->oui[0] << 16) | (ident->oui[1] << 8) |
		      ident->oui[2];

	switch (vendor_oui) {
	case LSPCON_VENDOR_MCA_OUI:
		lspcon->vendor = LSPCON_VENDOR_MCA;
		DRM_DEBUG_KMS("Vendor: Mega Chips\n");
		break;

	case LSPCON_VENDOR_PARADE_OUI:
		lspcon->vendor = LSPCON_VENDOR_PARADE;
		DRM_DEBUG_KMS("Vendor: Parade Tech\n");
		break;

	default:
		DRM_ERROR("Invalid/Unknown vendor OUI\n");
		return false;
	}

	return true;
}