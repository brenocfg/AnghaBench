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
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  FEAT_MGR_LCD2 ; 
 int FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int OMAP_DSS_CHANNEL_DIGIT ; 
 int OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_CHANNEL_LCD2 ; 
 int OMAP_DSS_CHANNEL_LCD3 ; 
 int OMAP_DSS_CHANNEL_WB ; 
#define  OMAP_DSS_GFX 131 
#define  OMAP_DSS_VIDEO1 130 
#define  OMAP_DSS_VIDEO2 129 
#define  OMAP_DSS_VIDEO3 128 
 int /*<<< orphan*/  dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum omap_channel dispc_ovl_get_channel_out(struct dispc_device *dispc,
						   enum omap_plane_id plane)
{
	int shift;
	u32 val;

	switch (plane) {
	case OMAP_DSS_GFX:
		shift = 8;
		break;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
	case OMAP_DSS_VIDEO3:
		shift = 16;
		break;
	default:
		BUG();
		return 0;
	}

	val = dispc_read_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));

	if (FLD_GET(val, shift, shift) == 1)
		return OMAP_DSS_CHANNEL_DIGIT;

	if (!dispc_has_feature(dispc, FEAT_MGR_LCD2))
		return OMAP_DSS_CHANNEL_LCD;

	switch (FLD_GET(val, 31, 30)) {
	case 0:
	default:
		return OMAP_DSS_CHANNEL_LCD;
	case 1:
		return OMAP_DSS_CHANNEL_LCD2;
	case 2:
		return OMAP_DSS_CHANNEL_LCD3;
	case 3:
		return OMAP_DSS_CHANNEL_WB;
	}
}