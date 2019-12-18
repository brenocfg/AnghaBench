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
struct TYPE_2__ {int right; int left; int bottom; int top; } ;
struct drm_cmdline_mode {int xres; int yres; int refresh_specified; int bpp_specified; int rb; int cvt; int interlace; int margins; scalar_t__ force; TYPE_1__ tv_margins; int /*<<< orphan*/  specified; } ;

/* Variables and functions */
 scalar_t__ DRM_FORCE_UNSPECIFIED ; 
 int /*<<< orphan*/  FAIL_ON (int) ; 
 int /*<<< orphan*/  drm_mode_parse_command_line_for_connector (char*,int /*<<< orphan*/ *,struct drm_cmdline_mode*) ; 
 int /*<<< orphan*/  no_connector ; 

__attribute__((used)) static int drm_cmdline_test_margin_options(void *ignored)
{
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,margin_right=14,margin_left=24,margin_bottom=36,margin_top=42",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.tv_margins.right != 14);
	FAIL_ON(mode.tv_margins.left != 24);
	FAIL_ON(mode.tv_margins.bottom != 36);
	FAIL_ON(mode.tv_margins.top != 42);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}