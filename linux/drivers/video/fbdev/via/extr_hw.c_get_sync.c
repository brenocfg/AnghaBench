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
typedef  int /*<<< orphan*/  u8 ;
struct fb_var_screeninfo {int sync; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  VIA_HSYNC_NEGATIVE ; 
 int /*<<< orphan*/  VIA_VSYNC_NEGATIVE ; 

__attribute__((used)) static u8 get_sync(struct fb_var_screeninfo *var)
{
	u8 polarity = 0;

	if (!(var->sync & FB_SYNC_HOR_HIGH_ACT))
		polarity |= VIA_HSYNC_NEGATIVE;
	if (!(var->sync & FB_SYNC_VERT_HIGH_ACT))
		polarity |= VIA_VSYNC_NEGATIVE;
	return polarity;
}