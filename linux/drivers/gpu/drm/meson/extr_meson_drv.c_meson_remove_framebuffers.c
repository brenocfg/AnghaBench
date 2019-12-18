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
struct apertures_struct {TYPE_1__* ranges; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ base; } ;

/* Variables and functions */
 struct apertures_struct* alloc_apertures (int) ; 
 int /*<<< orphan*/  drm_fb_helper_remove_conflicting_framebuffers (struct apertures_struct*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct apertures_struct*) ; 

__attribute__((used)) static void meson_remove_framebuffers(void)
{
	struct apertures_struct *ap;

	ap = alloc_apertures(1);
	if (!ap)
		return;

	/* The framebuffer can be located anywhere in RAM */
	ap->ranges[0].base = 0;
	ap->ranges[0].size = ~0;

	drm_fb_helper_remove_conflicting_framebuffers(ap, "meson-drm-fb",
						      false);
	kfree(ap);
}