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
struct TYPE_2__ {int vfmax; int vfmin; scalar_t__ hfmin; scalar_t__ hfmax; } ;
struct fb_info {TYPE_1__ monspecs; } ;

/* Variables and functions */
 scalar_t__ HFMAX ; 
 scalar_t__ HFMIN ; 
 scalar_t__ IS_DVT ; 
 int VFMAX ; 
 int VFMIN ; 
 scalar_t__ hsync1 ; 
 scalar_t__ hsync2 ; 
 int vsync1 ; 
 int vsync2 ; 

__attribute__((used)) static void i810_init_monspecs(struct fb_info *info)
{
	if (!hsync1)
		hsync1 = HFMIN;
	if (!hsync2) 
		hsync2 = HFMAX;
	if (!info->monspecs.hfmax)
		info->monspecs.hfmax = hsync2;
	if (!info->monspecs.hfmin)
		info->monspecs.hfmin = hsync1;
	if (hsync2 < hsync1)
		info->monspecs.hfmin = hsync2;

	if (!vsync1)
		vsync1 = VFMIN;
	if (!vsync2) 
		vsync2 = VFMAX;
	if (IS_DVT && vsync1 < 60)
		vsync1 = 60;
	if (!info->monspecs.vfmax)
		info->monspecs.vfmax = vsync2;
	if (!info->monspecs.vfmin)
		info->monspecs.vfmin = vsync1;
	if (vsync2 < vsync1) 
		info->monspecs.vfmin = vsync2;
}