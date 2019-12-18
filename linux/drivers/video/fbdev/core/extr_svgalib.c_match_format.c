#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ length; } ;
struct TYPE_14__ {scalar_t__ length; } ;
struct TYPE_12__ {scalar_t__ length; } ;
struct TYPE_10__ {scalar_t__ length; } ;
struct svga_fb_format {scalar_t__ bits_per_pixel; scalar_t__ nonstd; TYPE_8__ transp; TYPE_6__ blue; TYPE_4__ green; TYPE_2__ red; } ;
struct TYPE_15__ {scalar_t__ length; } ;
struct TYPE_13__ {scalar_t__ length; } ;
struct TYPE_11__ {scalar_t__ length; } ;
struct TYPE_9__ {scalar_t__ length; } ;
struct fb_var_screeninfo {scalar_t__ bits_per_pixel; scalar_t__ nonstd; TYPE_7__ transp; TYPE_5__ blue; TYPE_3__ green; TYPE_1__ red; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SVGA_FORMAT_END_VAL ; 

__attribute__((used)) static inline int match_format(const struct svga_fb_format *frm,
			       struct fb_var_screeninfo *var)
{
	int i = 0;
	int stored = -EINVAL;

	while (frm->bits_per_pixel != SVGA_FORMAT_END_VAL)
	{
		if ((var->bits_per_pixel == frm->bits_per_pixel) &&
		    (var->red.length     <= frm->red.length)     &&
		    (var->green.length   <= frm->green.length)   &&
		    (var->blue.length    <= frm->blue.length)    &&
		    (var->transp.length  <= frm->transp.length)  &&
		    (var->nonstd	 == frm->nonstd))
			return i;
		if (var->bits_per_pixel == frm->bits_per_pixel)
			stored = i;
		i++;
		frm++;
	}
	return stored;
}