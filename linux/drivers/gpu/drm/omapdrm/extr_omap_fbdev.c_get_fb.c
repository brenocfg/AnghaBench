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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct fb_info {struct drm_fb_helper* par; TYPE_1__ fix; } ;
struct drm_fb_helper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODULE_NAME ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_fb_helper *get_fb(struct fb_info *fbi)
{
	if (!fbi || strcmp(fbi->fix.id, MODULE_NAME)) {
		/* these are not the fb's you're looking for */
		return NULL;
	}
	return fbi->par;
}