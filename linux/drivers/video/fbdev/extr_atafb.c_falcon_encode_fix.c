#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fb_fix_screeninfo {int type_aux; int xpanstep; int ypanstep; int /*<<< orphan*/  accel; int /*<<< orphan*/  line_length; int /*<<< orphan*/  visual; void* type; scalar_t__ ywrapstep; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int f_shift; scalar_t__ mono; } ;
struct TYPE_4__ {TYPE_1__ falcon; } ;
struct atafb_par {int /*<<< orphan*/  next_line; TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_ATARIBLITT ; 
 void* FB_TYPE_INTERLEAVED_PLANES ; 
 void* FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  phys_screen_base ; 
 int /*<<< orphan*/  screen_len ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int falcon_encode_fix(struct fb_fix_screeninfo *fix,
			     struct atafb_par *par)
{
	strcpy(fix->id, "Atari Builtin");
	fix->smem_start = phys_screen_base;
	fix->smem_len = screen_len;
	fix->type = FB_TYPE_INTERLEAVED_PLANES;
	fix->type_aux = 2;
	fix->visual = FB_VISUAL_PSEUDOCOLOR;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	if (par->hw.falcon.mono) {
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->type_aux = 0;
		/* no smooth scrolling with longword aligned video mem */
		fix->xpanstep = 32;
	} else if (par->hw.falcon.f_shift & 0x100) {
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->type_aux = 0;
		/* Is this ok or should it be DIRECTCOLOR? */
		fix->visual = FB_VISUAL_TRUECOLOR;
		fix->xpanstep = 2;
	}
	fix->line_length = par->next_line;
	fix->accel = FB_ACCEL_ATARIBLITT;
	return 0;
}