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
struct drm_cmdline_mode {int xres; int yres; int refresh_specified; int bpp; int rb; int cvt; int interlace; int margins; scalar_t__ force; int /*<<< orphan*/  bpp_specified; int /*<<< orphan*/  specified; } ;

/* Variables and functions */
 scalar_t__ DRM_FORCE_UNSPECIFIED ; 
 int /*<<< orphan*/  FAIL_ON (int) ; 
 int /*<<< orphan*/  drm_mode_parse_command_line_for_connector (char*,int /*<<< orphan*/ *,struct drm_cmdline_mode*) ; 
 int /*<<< orphan*/  no_connector ; 

__attribute__((used)) static int drm_cmdline_test_res_bpp(void *ignored)
{
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}