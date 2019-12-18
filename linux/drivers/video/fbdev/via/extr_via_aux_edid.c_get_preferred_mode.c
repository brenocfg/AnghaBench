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
struct via_aux_drv {struct fb_monspecs* data; } ;
struct fb_videomode {int flag; } ;
struct fb_monspecs {int misc; int modedb_len; struct fb_videomode const* modedb; } ;

/* Variables and functions */
 int FB_MISC_1ST_DETAIL ; 
 int FB_MODE_IS_DETAILED ; 
 int FB_MODE_IS_FIRST ; 

__attribute__((used)) static const struct fb_videomode *get_preferred_mode(struct via_aux_drv *drv)
{
	struct fb_monspecs *spec = drv->data;
	int i;

	if (!spec || !spec->modedb || !(spec->misc & FB_MISC_1ST_DETAIL))
		return NULL;

	for (i = 0; i < spec->modedb_len; i++) {
		if (spec->modedb[i].flag & FB_MODE_IS_FIRST &&
			spec->modedb[i].flag & FB_MODE_IS_DETAILED)
			return &spec->modedb[i];
	}

	return NULL;
}