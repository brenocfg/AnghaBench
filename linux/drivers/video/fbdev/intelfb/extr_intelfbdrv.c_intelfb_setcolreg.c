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
struct intelfb_info {int depth; unsigned int* pseudo_palette; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,unsigned int,int) ; 
 struct intelfb_info* GET_DINFO (struct fb_info*) ; 
 int /*<<< orphan*/  intelfbhw_setcolreg (struct intelfb_info*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int intelfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			     unsigned blue, unsigned transp,
			     struct fb_info *info)
{
	struct intelfb_info *dinfo = GET_DINFO(info);

#if VERBOSE > 0
	DBG_MSG("intelfb_setcolreg: regno %d, depth %d\n", regno, dinfo->depth);
#endif

	if (regno > 255)
		return 1;

	if (dinfo->depth == 8) {
		red >>= 8;
		green >>= 8;
		blue >>= 8;

		intelfbhw_setcolreg(dinfo, regno, red, green, blue,
				    transp);
	}

	if (regno < 16) {
		switch (dinfo->depth) {
		case 15:
			dinfo->pseudo_palette[regno] = ((red & 0xf800) >>  1) |
				((green & 0xf800) >>  6) |
				((blue & 0xf800) >> 11);
			break;
		case 16:
			dinfo->pseudo_palette[regno] = (red & 0xf800) |
				((green & 0xfc00) >>  5) |
				((blue  & 0xf800) >> 11);
			break;
		case 24:
			dinfo->pseudo_palette[regno] = ((red & 0xff00) << 8) |
				(green & 0xff00) |
				((blue  & 0xff00) >> 8);
			break;
		}
	}

	return 0;
}