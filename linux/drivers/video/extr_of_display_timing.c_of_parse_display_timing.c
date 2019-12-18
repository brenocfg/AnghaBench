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
typedef  scalar_t__ u32 ;
struct display_timing {int flags; int /*<<< orphan*/  pixelclock; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  vactive; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  hactive; int /*<<< orphan*/  hfront_porch; int /*<<< orphan*/  hback_porch; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DE_HIGH ; 
 int DISPLAY_FLAGS_DE_LOW ; 
 int DISPLAY_FLAGS_DOUBLECLK ; 
 int DISPLAY_FLAGS_DOUBLESCAN ; 
 int DISPLAY_FLAGS_HSYNC_HIGH ; 
 int DISPLAY_FLAGS_HSYNC_LOW ; 
 int DISPLAY_FLAGS_INTERLACED ; 
 int DISPLAY_FLAGS_PIXDATA_NEGEDGE ; 
 int DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int DISPLAY_FLAGS_SYNC_NEGEDGE ; 
 int DISPLAY_FLAGS_SYNC_POSEDGE ; 
 int DISPLAY_FLAGS_VSYNC_HIGH ; 
 int DISPLAY_FLAGS_VSYNC_LOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct display_timing*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_property_read_bool (struct device_node const*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node const*,char*,scalar_t__*) ; 
 int parse_timing_property (struct device_node const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node const*) ; 

__attribute__((used)) static int of_parse_display_timing(const struct device_node *np,
		struct display_timing *dt)
{
	u32 val = 0;
	int ret = 0;

	memset(dt, 0, sizeof(*dt));

	ret |= parse_timing_property(np, "hback-porch", &dt->hback_porch);
	ret |= parse_timing_property(np, "hfront-porch", &dt->hfront_porch);
	ret |= parse_timing_property(np, "hactive", &dt->hactive);
	ret |= parse_timing_property(np, "hsync-len", &dt->hsync_len);
	ret |= parse_timing_property(np, "vback-porch", &dt->vback_porch);
	ret |= parse_timing_property(np, "vfront-porch", &dt->vfront_porch);
	ret |= parse_timing_property(np, "vactive", &dt->vactive);
	ret |= parse_timing_property(np, "vsync-len", &dt->vsync_len);
	ret |= parse_timing_property(np, "clock-frequency", &dt->pixelclock);

	dt->flags = 0;
	if (!of_property_read_u32(np, "vsync-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_VSYNC_HIGH :
				DISPLAY_FLAGS_VSYNC_LOW;
	if (!of_property_read_u32(np, "hsync-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_HSYNC_HIGH :
				DISPLAY_FLAGS_HSYNC_LOW;
	if (!of_property_read_u32(np, "de-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_DE_HIGH :
				DISPLAY_FLAGS_DE_LOW;
	if (!of_property_read_u32(np, "pixelclk-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_PIXDATA_POSEDGE :
				DISPLAY_FLAGS_PIXDATA_NEGEDGE;

	if (!of_property_read_u32(np, "syncclk-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_SYNC_POSEDGE :
				DISPLAY_FLAGS_SYNC_NEGEDGE;
	else if (dt->flags & (DISPLAY_FLAGS_PIXDATA_POSEDGE |
			      DISPLAY_FLAGS_PIXDATA_NEGEDGE))
		dt->flags |= dt->flags & DISPLAY_FLAGS_PIXDATA_POSEDGE ?
				DISPLAY_FLAGS_SYNC_POSEDGE :
				DISPLAY_FLAGS_SYNC_NEGEDGE;

	if (of_property_read_bool(np, "interlaced"))
		dt->flags |= DISPLAY_FLAGS_INTERLACED;
	if (of_property_read_bool(np, "doublescan"))
		dt->flags |= DISPLAY_FLAGS_DOUBLESCAN;
	if (of_property_read_bool(np, "doubleclk"))
		dt->flags |= DISPLAY_FLAGS_DOUBLECLK;

	if (ret) {
		pr_err("%pOF: error reading timing properties\n", np);
		return -EINVAL;
	}

	return 0;
}