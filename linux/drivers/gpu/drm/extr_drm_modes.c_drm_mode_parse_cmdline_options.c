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
struct drm_connector {int dummy; } ;
struct TYPE_2__ {unsigned int right; unsigned int left; unsigned int top; unsigned int bottom; } ;
struct drm_cmdline_mode {unsigned int rotation_reflection; TYPE_1__ tv_margins; } ;

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 unsigned int DRM_MODE_ROTATE_270 ; 
 unsigned int DRM_MODE_ROTATE_90 ; 
 int EINVAL ; 
 unsigned int simple_strtol (char const*,char**,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int drm_mode_parse_cmdline_options(char *str, size_t len,
					  const struct drm_connector *connector,
					  struct drm_cmdline_mode *mode)
{
	unsigned int rotation = 0;
	char *sep = str;

	while ((sep = strchr(sep, ','))) {
		char *delim, *option;

		option = sep + 1;
		delim = strchr(option, '=');
		if (!delim) {
			delim = strchr(option, ',');

			if (!delim)
				delim = str + len;
		}

		if (!strncmp(option, "rotate", delim - option)) {
			const char *value = delim + 1;
			unsigned int deg;

			deg = simple_strtol(value, &sep, 10);

			/* Make sure we have parsed something */
			if (sep == value)
				return -EINVAL;

			switch (deg) {
			case 0:
				rotation |= DRM_MODE_ROTATE_0;
				break;

			case 90:
				rotation |= DRM_MODE_ROTATE_90;
				break;

			case 180:
				rotation |= DRM_MODE_ROTATE_180;
				break;

			case 270:
				rotation |= DRM_MODE_ROTATE_270;
				break;

			default:
				return -EINVAL;
			}
		} else if (!strncmp(option, "reflect_x", delim - option)) {
			rotation |= DRM_MODE_REFLECT_X;
			sep = delim;
		} else if (!strncmp(option, "reflect_y", delim - option)) {
			rotation |= DRM_MODE_REFLECT_Y;
			sep = delim;
		} else if (!strncmp(option, "margin_right", delim - option)) {
			const char *value = delim + 1;
			unsigned int margin;

			margin = simple_strtol(value, &sep, 10);

			/* Make sure we have parsed something */
			if (sep == value)
				return -EINVAL;

			mode->tv_margins.right = margin;
		} else if (!strncmp(option, "margin_left", delim - option)) {
			const char *value = delim + 1;
			unsigned int margin;

			margin = simple_strtol(value, &sep, 10);

			/* Make sure we have parsed something */
			if (sep == value)
				return -EINVAL;

			mode->tv_margins.left = margin;
		} else if (!strncmp(option, "margin_top", delim - option)) {
			const char *value = delim + 1;
			unsigned int margin;

			margin = simple_strtol(value, &sep, 10);

			/* Make sure we have parsed something */
			if (sep == value)
				return -EINVAL;

			mode->tv_margins.top = margin;
		} else if (!strncmp(option, "margin_bottom", delim - option)) {
			const char *value = delim + 1;
			unsigned int margin;

			margin = simple_strtol(value, &sep, 10);

			/* Make sure we have parsed something */
			if (sep == value)
				return -EINVAL;

			mode->tv_margins.bottom = margin;
		} else {
			return -EINVAL;
		}
	}

	mode->rotation_reflection = rotation;

	return 0;
}