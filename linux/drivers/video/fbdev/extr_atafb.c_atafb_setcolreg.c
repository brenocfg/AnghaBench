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
typedef  int u_int ;
struct fb_info {TYPE_1__* fbops; } ;
struct TYPE_2__ {int (* fb_setcolreg ) (int,int,int,int,int,struct fb_info*) ;} ;

/* Variables and functions */
 int stub1 (int,int,int,int,int,struct fb_info*) ; 

__attribute__((used)) static int atafb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			   u_int transp, struct fb_info *info)
{
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	return info->fbops->fb_setcolreg(regno, red, green, blue, transp, info);
}