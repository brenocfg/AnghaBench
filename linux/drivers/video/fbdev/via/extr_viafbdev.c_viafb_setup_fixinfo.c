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
struct viafb_par {int /*<<< orphan*/  fbmem_free; int /*<<< orphan*/  fbmem; } ;
struct fb_fix_screeninfo {int ypanstep; scalar_t__ ywrapstep; scalar_t__ xpanstep; int /*<<< orphan*/  visual; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  accel; } ;
struct TYPE_4__ {TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_VIA_UNICHROME ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  memset (struct fb_fix_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_name ; 
 TYPE_2__* viafbinfo ; 

__attribute__((used)) static void viafb_setup_fixinfo(struct fb_fix_screeninfo *fix,
	struct viafb_par *viaparinfo)
{
	memset(fix, 0, sizeof(struct fb_fix_screeninfo));
	strcpy(fix->id, viafb_name);

	fix->smem_start = viaparinfo->fbmem;
	fix->smem_len = viaparinfo->fbmem_free;

	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;
	fix->visual = FB_VISUAL_TRUECOLOR;

	fix->xpanstep = fix->ywrapstep = 0;
	fix->ypanstep = 1;

	/* Just tell the accel name */
	viafbinfo->fix.accel = FB_ACCEL_VIA_UNICHROME;
}