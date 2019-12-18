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
struct svga_fb_format {int /*<<< orphan*/  xpanstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  nonstd; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  bits_per_pixel; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  nonstd; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  bits_per_pixel; } ;
struct fb_fix_screeninfo {int /*<<< orphan*/  xpanstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  type_aux; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int match_format (struct svga_fb_format const*,struct fb_var_screeninfo*) ; 

int svga_match_format(const struct svga_fb_format *frm,
		      struct fb_var_screeninfo *var,
		      struct fb_fix_screeninfo *fix)
{
	int i = match_format(frm, var);

	if (i >= 0) {
		var->bits_per_pixel = frm[i].bits_per_pixel;
		var->red            = frm[i].red;
		var->green          = frm[i].green;
		var->blue           = frm[i].blue;
		var->transp         = frm[i].transp;
		var->nonstd         = frm[i].nonstd;
		if (fix != NULL) {
			fix->type      = frm[i].type;
			fix->type_aux  = frm[i].type_aux;
			fix->visual    = frm[i].visual;
			fix->xpanstep  = frm[i].xpanstep;
		}
	}

	return i;
}