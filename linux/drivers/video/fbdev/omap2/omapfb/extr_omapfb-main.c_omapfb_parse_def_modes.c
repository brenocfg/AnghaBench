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
struct omapfb2_device {int num_displays; TYPE_1__* displays; } ;
struct omap_dss_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct omap_dss_device* dssdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  def_mode ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omapfb_set_def_mode (struct omapfb2_device*,struct omap_dss_device*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int omapfb_parse_def_modes(struct omapfb2_device *fbdev)
{
	char *str, *options, *this_opt;
	int r = 0;

	str = kstrdup(def_mode, GFP_KERNEL);
	if (!str)
		return -ENOMEM;
	options = str;

	while (!r && (this_opt = strsep(&options, ",")) != NULL) {
		char *p, *display_str, *mode_str;
		struct omap_dss_device *display;
		int i;

		p = strchr(this_opt, ':');
		if (!p) {
			r = -EINVAL;
			break;
		}

		*p = 0;
		display_str = this_opt;
		mode_str = p + 1;

		display = NULL;
		for (i = 0; i < fbdev->num_displays; ++i) {
			if (strcmp(fbdev->displays[i].dssdev->name,
						display_str) == 0) {
				display = fbdev->displays[i].dssdev;
				break;
			}
		}

		if (!display) {
			r = -EINVAL;
			break;
		}

		r = omapfb_set_def_mode(fbdev, display, mode_str);
		if (r)
			break;
	}

	kfree(str);

	return r;
}