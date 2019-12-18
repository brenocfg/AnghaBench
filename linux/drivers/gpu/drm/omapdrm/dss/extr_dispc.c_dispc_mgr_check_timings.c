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
struct videomode {int flags; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hback_porch; int /*<<< orphan*/  hfront_porch; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  pixelclock; int /*<<< orphan*/  vactive; int /*<<< orphan*/  hactive; } ;
struct dispc_device {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int DISPLAY_FLAGS_INTERLACED ; 
 int MODE_BAD ; 
 int MODE_OK ; 
 int /*<<< orphan*/  _dispc_lcd_timings_ok (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dispc_mgr_pclk_ok (struct dispc_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dispc_mgr_size_ok (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dss_mgr_is_lcd (int) ; 

__attribute__((used)) static int dispc_mgr_check_timings(struct dispc_device *dispc,
				   enum omap_channel channel,
				   const struct videomode *vm)
{
	if (!_dispc_mgr_size_ok(dispc, vm->hactive, vm->vactive))
		return MODE_BAD;

	if (!_dispc_mgr_pclk_ok(dispc, channel, vm->pixelclock))
		return MODE_BAD;

	if (dss_mgr_is_lcd(channel)) {
		/* TODO: OMAP4+ supports interlace for LCD outputs */
		if (vm->flags & DISPLAY_FLAGS_INTERLACED)
			return MODE_BAD;

		if (!_dispc_lcd_timings_ok(dispc, vm->hsync_len,
				vm->hfront_porch, vm->hback_porch,
				vm->vsync_len, vm->vfront_porch,
				vm->vback_porch))
			return MODE_BAD;
	}

	return MODE_OK;
}