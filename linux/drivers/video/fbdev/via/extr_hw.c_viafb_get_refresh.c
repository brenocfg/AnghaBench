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
struct fb_videomode {int refresh; } ;

/* Variables and functions */
 int abs (int) ; 
 struct fb_videomode* viafb_get_best_mode (int,int,int) ; 

int viafb_get_refresh(int hres, int vres, u32 long_refresh)
{
	const struct fb_videomode *best;

	best = viafb_get_best_mode(hres, vres, long_refresh);
	if (!best)
		return 60;

	if (abs(best->refresh - long_refresh) > 3) {
		if (hres == 1200 && vres == 900)
			return 49; /* OLPC DCON only supports 50 Hz */
		else
			return 60;
	}

	return best->refresh;
}