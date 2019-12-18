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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_fbdev {TYPE_1__ helper; int /*<<< orphan*/  preferred_bpp; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 scalar_t__ drm_fb_helper_initial_config (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_fbdev_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_fbdev_initial_config(void *data, async_cookie_t cookie)
{
	struct intel_fbdev *ifbdev = data;

	/* Due to peculiar init order wrt to hpd handling this is separate. */
	if (drm_fb_helper_initial_config(&ifbdev->helper,
					 ifbdev->preferred_bpp))
		intel_fbdev_unregister(to_i915(ifbdev->helper.dev));
}