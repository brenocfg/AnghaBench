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
struct drm_cmdline_mode {int refresh_specified; int bpp; int /*<<< orphan*/  bpp_specified; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_ON (int) ; 
 int /*<<< orphan*/  drm_mode_parse_command_line_for_connector (char*,int /*<<< orphan*/ *,struct drm_cmdline_mode*) ; 
 int /*<<< orphan*/  no_connector ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int drm_cmdline_test_name_bpp(void *ignored)
{
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("NTSC-24",
							   &no_connector,
							   &mode));
	FAIL_ON(strcmp(mode.name, "NTSC"));

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	return 0;
}