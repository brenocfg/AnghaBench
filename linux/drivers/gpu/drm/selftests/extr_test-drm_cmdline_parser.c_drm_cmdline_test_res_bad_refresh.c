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
struct drm_cmdline_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_parse_command_line_for_connector (char*,int /*<<< orphan*/ *,struct drm_cmdline_mode*) ; 
 int /*<<< orphan*/  no_connector ; 

__attribute__((used)) static int drm_cmdline_test_res_bad_refresh(void *ignored)
{
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480@refresh",
							  &no_connector,
							  &mode));

	return 0;
}