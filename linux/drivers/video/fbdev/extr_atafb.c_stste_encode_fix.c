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
struct fb_fix_screeninfo {int type_aux; int xpanstep; int ypanstep; int /*<<< orphan*/  accel; int /*<<< orphan*/  line_length; scalar_t__ ywrapstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int mode; } ;
struct TYPE_4__ {TYPE_1__ st; } ;
struct atafb_par {int /*<<< orphan*/  next_line; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTD_SHIFTER ; 
 int /*<<< orphan*/  FB_ACCEL_ATARIBLITT ; 
 int /*<<< orphan*/  FB_TYPE_INTERLEAVED_PLANES ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_MONO10 ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int ST_HIGH ; 
 int /*<<< orphan*/  phys_screen_base ; 
 int /*<<< orphan*/  screen_len ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int stste_encode_fix(struct fb_fix_screeninfo *fix,
			    struct atafb_par *par)
{
	int mode;

	strcpy(fix->id, "Atari Builtin");
	fix->smem_start = phys_screen_base;
	fix->smem_len = screen_len;
	fix->type = FB_TYPE_INTERLEAVED_PLANES;
	fix->type_aux = 2;
	fix->visual = FB_VISUAL_PSEUDOCOLOR;
	mode = par->hw.st.mode & 3;
	if (mode == ST_HIGH) {
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->type_aux = 0;
		fix->visual = FB_VISUAL_MONO10;
	}
	if (ATARIHW_PRESENT(EXTD_SHIFTER)) {
		fix->xpanstep = 16;
		fix->ypanstep = 1;
	} else {
		fix->xpanstep = 0;
		fix->ypanstep = 0;
	}
	fix->ywrapstep = 0;
	fix->line_length = par->next_line;
	fix->accel = FB_ACCEL_ATARIBLITT;
	return 0;
}