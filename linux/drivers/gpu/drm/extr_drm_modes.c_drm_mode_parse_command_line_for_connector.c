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
struct drm_connector {int dummy; } ;
struct drm_cmdline_mode {int specified; int bpp_specified; int refresh_specified; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int DRM_DISPLAY_MODE_LEN ; 
 int drm_mode_parse_cmdline_bpp (char*,char**,struct drm_cmdline_mode*) ; 
 int drm_mode_parse_cmdline_extra (char const*,int,int,struct drm_connector const*,struct drm_cmdline_mode*) ; 
 int drm_mode_parse_cmdline_options (char*,int,struct drm_connector const*,struct drm_cmdline_mode*) ; 
 int drm_mode_parse_cmdline_refresh (char*,char**,struct drm_cmdline_mode*) ; 
 int drm_mode_parse_cmdline_res_mode (char const*,unsigned int,int,struct drm_connector const*,struct drm_cmdline_mode*) ; 
 int /*<<< orphan*/  drm_named_mode_is_in_whitelist (char const*,unsigned int) ; 
 char* fb_mode_option ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 char* max (char*,char*) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 

bool drm_mode_parse_command_line_for_connector(const char *mode_option,
					       const struct drm_connector *connector,
					       struct drm_cmdline_mode *mode)
{
	const char *name;
	bool named_mode = false, parse_extras = false;
	unsigned int bpp_off = 0, refresh_off = 0, options_off = 0;
	unsigned int mode_end = 0;
	char *bpp_ptr = NULL, *refresh_ptr = NULL, *extra_ptr = NULL;
	char *options_ptr = NULL;
	char *bpp_end_ptr = NULL, *refresh_end_ptr = NULL;
	int ret;

#ifdef CONFIG_FB
	if (!mode_option)
		mode_option = fb_mode_option;
#endif

	if (!mode_option) {
		mode->specified = false;
		return false;
	}

	name = mode_option;

	/*
	 * This is a bit convoluted. To differentiate between the
	 * named modes and poorly formatted resolutions, we need a
	 * bunch of things:
	 *   - We need to make sure that the first character (which
	 *     would be our resolution in X) is a digit.
	 *   - If not, then it's either a named mode or a force on/off.
	 *     To distinguish between the two, we need to run the
	 *     extra parsing function, and if not, then we consider it
	 *     a named mode.
	 *
	 * If this isn't enough, we should add more heuristics here,
	 * and matching unit-tests.
	 */
	if (!isdigit(name[0]) && name[0] != 'x') {
		unsigned int namelen = strlen(name);

		/*
		 * Only the force on/off options can be in that case,
		 * and they all take a single character.
		 */
		if (namelen == 1) {
			ret = drm_mode_parse_cmdline_extra(name, namelen, true,
							   connector, mode);
			if (!ret)
				return true;
		}

		named_mode = true;
	}

	/* Try to locate the bpp and refresh specifiers, if any */
	bpp_ptr = strchr(name, '-');
	if (bpp_ptr) {
		bpp_off = bpp_ptr - name;
		mode->bpp_specified = true;
	}

	refresh_ptr = strchr(name, '@');
	if (refresh_ptr) {
		if (named_mode)
			return false;

		refresh_off = refresh_ptr - name;
		mode->refresh_specified = true;
	}

	/* Locate the start of named options */
	options_ptr = strchr(name, ',');
	if (options_ptr)
		options_off = options_ptr - name;

	/* Locate the end of the name / resolution, and parse it */
	if (bpp_ptr) {
		mode_end = bpp_off;
	} else if (refresh_ptr) {
		mode_end = refresh_off;
	} else if (options_ptr) {
		mode_end = options_off;
	} else {
		mode_end = strlen(name);
		parse_extras = true;
	}

	if (named_mode) {
		if (mode_end + 1 > DRM_DISPLAY_MODE_LEN)
			return false;

		if (!drm_named_mode_is_in_whitelist(name, mode_end))
			return false;

		strscpy(mode->name, name, mode_end + 1);
	} else {
		ret = drm_mode_parse_cmdline_res_mode(name, mode_end,
						      parse_extras,
						      connector,
						      mode);
		if (ret)
			return false;
	}
	mode->specified = true;

	if (bpp_ptr) {
		ret = drm_mode_parse_cmdline_bpp(bpp_ptr, &bpp_end_ptr, mode);
		if (ret)
			return false;
	}

	if (refresh_ptr) {
		ret = drm_mode_parse_cmdline_refresh(refresh_ptr,
						     &refresh_end_ptr, mode);
		if (ret)
			return false;
	}

	/*
	 * Locate the end of the bpp / refresh, and parse the extras
	 * if relevant
	 */
	if (bpp_ptr && refresh_ptr)
		extra_ptr = max(bpp_end_ptr, refresh_end_ptr);
	else if (bpp_ptr)
		extra_ptr = bpp_end_ptr;
	else if (refresh_ptr)
		extra_ptr = refresh_end_ptr;

	if (extra_ptr &&
	    extra_ptr != options_ptr) {
		int len = strlen(name) - (extra_ptr - name);

		ret = drm_mode_parse_cmdline_extra(extra_ptr, len, false,
						   connector, mode);
		if (ret)
			return false;
	}

	if (options_ptr) {
		int len = strlen(name) - (options_ptr - name);

		ret = drm_mode_parse_cmdline_options(options_ptr, len,
						     connector, mode);
		if (ret)
			return false;
	}

	return true;
}