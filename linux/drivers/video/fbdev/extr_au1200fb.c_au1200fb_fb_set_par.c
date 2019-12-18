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
struct fb_info {struct au1200fb_device* par; } ;
struct au1200fb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1200_setmode (struct au1200fb_device*) ; 
 int /*<<< orphan*/  au1200fb_update_fbinfo (struct fb_info*) ; 

__attribute__((used)) static int au1200fb_fb_set_par(struct fb_info *fbi)
{
	struct au1200fb_device *fbdev = fbi->par;

	au1200fb_update_fbinfo(fbi);
	au1200_setmode(fbdev);

	return 0;
}