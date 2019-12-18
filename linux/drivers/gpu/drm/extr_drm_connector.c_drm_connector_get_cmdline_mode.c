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
struct drm_cmdline_mode {int refresh; scalar_t__ interlace; scalar_t__ margins; scalar_t__ rb; scalar_t__ refresh_specified; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  name; scalar_t__ force; } ;
struct drm_connector {int /*<<< orphan*/  name; scalar_t__ force; struct drm_cmdline_mode cmdline_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_get_connector_force_name (scalar_t__) ; 
 int /*<<< orphan*/  drm_mode_parse_command_line_for_connector (char*,struct drm_connector*,struct drm_cmdline_mode*) ; 
 scalar_t__ fb_get_options (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static void drm_connector_get_cmdline_mode(struct drm_connector *connector)
{
	struct drm_cmdline_mode *mode = &connector->cmdline_mode;
	char *option = NULL;

	if (fb_get_options(connector->name, &option))
		return;

	if (!drm_mode_parse_command_line_for_connector(option,
						       connector,
						       mode))
		return;

	if (mode->force) {
		DRM_INFO("forcing %s connector %s\n", connector->name,
			 drm_get_connector_force_name(mode->force));
		connector->force = mode->force;
	}

	DRM_DEBUG_KMS("cmdline mode for connector %s %s %dx%d@%dHz%s%s%s\n",
		      connector->name, mode->name,
		      mode->xres, mode->yres,
		      mode->refresh_specified ? mode->refresh : 60,
		      mode->rb ? " reduced blanking" : "",
		      mode->margins ? " with margins" : "",
		      mode->interlace ?  " interlaced" : "");
}