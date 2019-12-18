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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {TYPE_1__ transp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCCR3_BPP (int) ; 
 int /*<<< orphan*/  LCCR3_PDFOR_0 ; 
 int /*<<< orphan*/  LCCR3_PDFOR_2 ; 
 int /*<<< orphan*/  LCCR3_PDFOR_3 ; 
 int pxafb_var_to_bpp (struct fb_var_screeninfo*) ; 
 int var_to_depth (struct fb_var_screeninfo*) ; 

__attribute__((used)) static uint32_t pxafb_var_to_lccr3(struct fb_var_screeninfo *var)
{
	int bpp = pxafb_var_to_bpp(var);
	uint32_t lccr3;

	if (bpp < 0)
		return 0;

	lccr3 = LCCR3_BPP(bpp);

	switch (var_to_depth(var)) {
	case 16: lccr3 |= var->transp.length ? LCCR3_PDFOR_3 : 0; break;
	case 18: lccr3 |= LCCR3_PDFOR_3; break;
	case 24: lccr3 |= var->transp.length ? LCCR3_PDFOR_2 : LCCR3_PDFOR_3;
		 break;
	case 19:
	case 25: lccr3 |= LCCR3_PDFOR_0; break;
	}
	return lccr3;
}