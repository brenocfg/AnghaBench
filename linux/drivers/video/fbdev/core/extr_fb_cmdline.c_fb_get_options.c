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

/* Variables and functions */
 int FB_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ fb_mode_option ; 
 char* kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ofonly ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char** video_options ; 

int fb_get_options(const char *name, char **option)
{
	char *opt, *options = NULL;
	int retval = 0;
	int name_len = strlen(name), i;

	if (name_len && ofonly && strncmp(name, "offb", 4))
		retval = 1;

	if (name_len && !retval) {
		for (i = 0; i < FB_MAX; i++) {
			if (video_options[i] == NULL)
				continue;
			if (!video_options[i][0])
				continue;
			opt = video_options[i];
			if (!strncmp(name, opt, name_len) &&
			    opt[name_len] == ':')
				options = opt + name_len + 1;
		}
	}
	/* No match, pass global option */
	if (!options && option && fb_mode_option)
		options = kstrdup(fb_mode_option, GFP_KERNEL);
	if (options && !strncmp(options, "off", 3))
		retval = 1;

	if (option)
		*option = options;

	return retval;
}