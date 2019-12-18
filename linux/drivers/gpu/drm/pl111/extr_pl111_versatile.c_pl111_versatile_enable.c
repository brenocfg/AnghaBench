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
typedef  int u32 ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR1555 137 
#define  DRM_FORMAT_ABGR8888 136 
#define  DRM_FORMAT_ARGB1555 135 
#define  DRM_FORMAT_ARGB8888 134 
#define  DRM_FORMAT_BGR565 133 
#define  DRM_FORMAT_RGB565 132 
#define  DRM_FORMAT_XBGR1555 131 
#define  DRM_FORMAT_XBGR8888 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 int /*<<< orphan*/  SYS_CLCD ; 
 int /*<<< orphan*/  SYS_CLCD_CONNECTOR_MASK ; 
 int SYS_CLCD_MODE_5551 ; 
 int SYS_CLCD_MODE_565_B_LSB ; 
 int SYS_CLCD_MODE_565_R_LSB ; 
 int SYS_CLCD_MODE_888 ; 
 int /*<<< orphan*/  SYS_CLCD_MODE_MASK ; 
 int SYS_CLCD_NLCDIOON ; 
 int SYS_CLCD_PWR3V5SWITCH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  versatile_syscon_map ; 

__attribute__((used)) static void pl111_versatile_enable(struct drm_device *drm, u32 format)
{
	u32 val = 0;

	dev_info(drm->dev, "enable Versatile CLCD connectors\n");

	switch (format) {
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_XRGB8888:
		val |= SYS_CLCD_MODE_888;
		break;
	case DRM_FORMAT_BGR565:
		val |= SYS_CLCD_MODE_565_R_LSB;
		break;
	case DRM_FORMAT_RGB565:
		val |= SYS_CLCD_MODE_565_B_LSB;
		break;
	case DRM_FORMAT_ABGR1555:
	case DRM_FORMAT_XBGR1555:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_XRGB1555:
		val |= SYS_CLCD_MODE_5551;
		break;
	default:
		dev_err(drm->dev, "unhandled format on Versatile 0x%08x\n",
			format);
		break;
	}

	/* Set up the MUX */
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_MODE_MASK,
			   val);

	/* Then enable the display */
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_CONNECTOR_MASK,
			   SYS_CLCD_NLCDIOON | SYS_CLCD_PWR3V5SWITCH);
}