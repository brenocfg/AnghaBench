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
struct fb_cvt_data {int yres; int interlace; int v_margin; } ;

/* Variables and functions */
 scalar_t__ fb_cvt_vbi_lines (struct fb_cvt_data*) ; 

__attribute__((used)) static u32 fb_cvt_vtotal(struct fb_cvt_data *cvt)
{
	u32 vtotal = cvt->yres/cvt->interlace;

	vtotal += 2 * cvt->v_margin + cvt->interlace/2 + fb_cvt_vbi_lines(cvt);
	vtotal |= cvt->interlace/2;

	return vtotal;
}