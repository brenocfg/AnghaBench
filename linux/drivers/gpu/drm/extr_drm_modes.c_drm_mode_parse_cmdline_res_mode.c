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
struct drm_cmdline_mode {int xres; int yres; int cvt; int rb; } ;

/* Variables and functions */
 int EINVAL ; 
 int drm_mode_parse_cmdline_extra (char*,int,int,struct drm_connector const*,struct drm_cmdline_mode*) ; 
 int simple_strtol (char const*,char**,int) ; 

__attribute__((used)) static int drm_mode_parse_cmdline_res_mode(const char *str, unsigned int length,
					   bool extras,
					   const struct drm_connector *connector,
					   struct drm_cmdline_mode *mode)
{
	const char *str_start = str;
	bool rb = false, cvt = false;
	int xres = 0, yres = 0;
	int remaining, i;
	char *end_ptr;

	xres = simple_strtol(str, &end_ptr, 10);
	if (end_ptr == str)
		return -EINVAL;

	if (end_ptr[0] != 'x')
		return -EINVAL;
	end_ptr++;

	str = end_ptr;
	yres = simple_strtol(str, &end_ptr, 10);
	if (end_ptr == str)
		return -EINVAL;

	remaining = length - (end_ptr - str_start);
	if (remaining < 0)
		return -EINVAL;

	for (i = 0; i < remaining; i++) {
		switch (end_ptr[i]) {
		case 'M':
			cvt = true;
			break;
		case 'R':
			rb = true;
			break;
		default:
			/*
			 * Try to pass that to our extras parsing
			 * function to handle the case where the
			 * extras are directly after the resolution
			 */
			if (extras) {
				int ret = drm_mode_parse_cmdline_extra(end_ptr + i,
								       1,
								       false,
								       connector,
								       mode);
				if (ret)
					return ret;
			} else {
				return -EINVAL;
			}
		}
	}

	mode->xres = xres;
	mode->yres = yres;
	mode->cvt = cvt;
	mode->rb = rb;

	return 0;
}