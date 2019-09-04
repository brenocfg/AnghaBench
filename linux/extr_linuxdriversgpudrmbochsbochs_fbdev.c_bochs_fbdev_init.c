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
struct TYPE_2__ {int /*<<< orphan*/  helper; } ;
struct bochs_device {TYPE_1__ fb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_fb_helper_funcs ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int drm_fb_helper_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (int /*<<< orphan*/ ) ; 

int bochs_fbdev_init(struct bochs_device *bochs)
{
	int ret;

	drm_fb_helper_prepare(bochs->dev, &bochs->fb.helper,
			      &bochs_fb_helper_funcs);

	ret = drm_fb_helper_init(bochs->dev, &bochs->fb.helper, 1);
	if (ret)
		return ret;

	ret = drm_fb_helper_single_add_all_connectors(&bochs->fb.helper);
	if (ret)
		goto fini;

	drm_helper_disable_unused_functions(bochs->dev);

	ret = drm_fb_helper_initial_config(&bochs->fb.helper, 32);
	if (ret)
		goto fini;

	return 0;

fini:
	drm_fb_helper_fini(&bochs->fb.helper);
	return ret;
}