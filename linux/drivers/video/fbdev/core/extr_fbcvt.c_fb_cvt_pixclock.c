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
typedef  int u32 ;
struct fb_cvt_data {int flags; int f_refresh; int vtotal; int htotal; int hperiod; } ;

/* Variables and functions */
 int FB_CVT_FLAG_REDUCED_BLANK ; 

__attribute__((used)) static u32 fb_cvt_pixclock(struct fb_cvt_data *cvt)
{
	u32 pixclock;

	if (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK)
		pixclock = (cvt->f_refresh * cvt->vtotal * cvt->htotal)/1000;
	else
		pixclock = (cvt->htotal * 1000000)/cvt->hperiod;

	pixclock /= 250;
	pixclock *= 250;
	pixclock *= 1000;

	return pixclock;
}