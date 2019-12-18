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
struct nvidia_par {int dummy; } ;
struct fb_info {struct nvidia_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_POINT ; 
 int /*<<< orphan*/  NVDmaNext (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVDmaStart (struct fb_info*,struct nvidia_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void NVSetClippingRectangle(struct fb_info *info, int x1, int y1,
				   int x2, int y2)
{
	struct nvidia_par *par = info->par;
	int h = y2 - y1 + 1;
	int w = x2 - x1 + 1;

	NVDmaStart(info, par, CLIP_POINT, 2);
	NVDmaNext(par, (y1 << 16) | x1);
	NVDmaNext(par, (h << 16) | w);
}