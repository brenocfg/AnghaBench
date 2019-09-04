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
struct sii8620 {int* devcap; } ;
struct drm_display_mode {int dummy; } ;
struct drm_bridge {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 size_t MHL_DCAP_VID_LINK_MODE ; 
 int MHL_DCAP_VID_LINK_PPIXEL ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_OK ; 
 struct sii8620* bridge_to_sii8620 (struct drm_bridge*) ; 
 int sii8620_is_packing_required (struct sii8620*,struct drm_display_mode const*) ; 

__attribute__((used)) static enum drm_mode_status sii8620_mode_valid(struct drm_bridge *bridge,
					 const struct drm_display_mode *mode)
{
	struct sii8620 *ctx = bridge_to_sii8620(bridge);
	int pack_required = sii8620_is_packing_required(ctx, mode);
	bool can_pack = ctx->devcap[MHL_DCAP_VID_LINK_MODE] &
			MHL_DCAP_VID_LINK_PPIXEL;

	switch (pack_required) {
	case 0:
		return MODE_OK;
	case 1:
		return (can_pack) ? MODE_OK : MODE_CLOCK_HIGH;
	default:
		return MODE_CLOCK_HIGH;
	}
}