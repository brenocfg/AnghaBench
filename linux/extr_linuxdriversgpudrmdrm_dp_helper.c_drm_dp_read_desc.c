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
struct drm_dp_dpcd_ident {int hw_rev; int /*<<< orphan*/  sw_minor_rev; int /*<<< orphan*/  sw_major_rev; int /*<<< orphan*/  device_id; int /*<<< orphan*/  oui; } ;
struct drm_dp_desc {int /*<<< orphan*/  quirks; struct drm_dp_dpcd_ident ident; } ;
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 unsigned int DP_BRANCH_OUI ; 
 unsigned int DP_SINK_OUI ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_dp_dpcd_read (struct drm_dp_aux*,unsigned int,struct drm_dp_dpcd_ident*,int) ; 
 int /*<<< orphan*/  drm_dp_get_quirks (struct drm_dp_dpcd_ident*,int) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 

int drm_dp_read_desc(struct drm_dp_aux *aux, struct drm_dp_desc *desc,
		     bool is_branch)
{
	struct drm_dp_dpcd_ident *ident = &desc->ident;
	unsigned int offset = is_branch ? DP_BRANCH_OUI : DP_SINK_OUI;
	int ret, dev_id_len;

	ret = drm_dp_dpcd_read(aux, offset, ident, sizeof(*ident));
	if (ret < 0)
		return ret;

	desc->quirks = drm_dp_get_quirks(ident, is_branch);

	dev_id_len = strnlen(ident->device_id, sizeof(ident->device_id));

	DRM_DEBUG_KMS("DP %s: OUI %*phD dev-ID %*pE HW-rev %d.%d SW-rev %d.%d quirks 0x%04x\n",
		      is_branch ? "branch" : "sink",
		      (int)sizeof(ident->oui), ident->oui,
		      dev_id_len, ident->device_id,
		      ident->hw_rev >> 4, ident->hw_rev & 0xf,
		      ident->sw_major_rev, ident->sw_minor_rev,
		      desc->quirks);

	return 0;
}