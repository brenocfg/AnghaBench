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
typedef  int uint ;
struct hvfb_par {scalar_t__ synthvid_version; } ;
struct fb_info {struct hvfb_par* par; } ;

/* Variables and functions */
 int HVFB_HEIGHT_MIN ; 
 int HVFB_WIDTH_MIN ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int SYNTHVID_FB_SIZE_WIN8 ; 
 int SYNTHVID_HEIGHT_MAX_WIN7 ; 
 scalar_t__ SYNTHVID_VERSION_WIN7 ; 
 scalar_t__ SYNTHVID_VERSION_WIN8 ; 
 int SYNTHVID_WIDTH_MAX_WIN7 ; 
 scalar_t__ fb_get_options (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ kstrtouint (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int screen_depth ; 
 int screen_height ; 
 int screen_width ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void hvfb_get_option(struct fb_info *info)
{
	struct hvfb_par *par = info->par;
	char *opt = NULL, *p;
	uint x = 0, y = 0;

	if (fb_get_options(KBUILD_MODNAME, &opt) || !opt || !*opt)
		return;

	p = strsep(&opt, "x");
	if (!*p || kstrtouint(p, 0, &x) ||
	    !opt || !*opt || kstrtouint(opt, 0, &y)) {
		pr_err("Screen option is invalid: skipped\n");
		return;
	}

	if (x < HVFB_WIDTH_MIN || y < HVFB_HEIGHT_MIN ||
	    (par->synthvid_version == SYNTHVID_VERSION_WIN8 &&
	     x * y * screen_depth / 8 > SYNTHVID_FB_SIZE_WIN8) ||
	    (par->synthvid_version == SYNTHVID_VERSION_WIN7 &&
	     (x > SYNTHVID_WIDTH_MAX_WIN7 || y > SYNTHVID_HEIGHT_MAX_WIN7))) {
		pr_err("Screen resolution option is out of range: skipped\n");
		return;
	}

	screen_width = x;
	screen_height = y;
	return;
}