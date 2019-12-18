#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int yres; int xres; int bits_per_pixel; } ;
struct TYPE_4__ {int line_length; } ;
struct TYPE_6__ {TYPE_2__ var; TYPE_1__ fix; scalar_t__ screen_base; } ;
struct stifb_info {int id; TYPE_3__ info; } ;

/* Variables and functions */
 int CRX24_OVERLAY_PLANES ; 
 int /*<<< orphan*/  CRX24_SETUP_RAMDAC (struct stifb_info*) ; 
 int /*<<< orphan*/  CRX24_SET_OVLY_MASK (struct stifb_info*) ; 
 int /*<<< orphan*/  SETUP_FB (struct stifb_info*) ; 
 int /*<<< orphan*/  fb_memset (scalar_t__,int,int) ; 

__attribute__((used)) static void
rattlerSetupPlanes(struct stifb_info *fb)
{
	int saved_id, y;

 	/* Write RAMDAC pixel read mask register so all overlay
	 * planes are display-enabled.  (CRX24 uses Bt462 pixel
	 * read mask register for overlay planes, not image planes).
	 */
	CRX24_SETUP_RAMDAC(fb);
    
	/* change fb->id temporarily to fool SETUP_FB() */
	saved_id = fb->id;
	fb->id = CRX24_OVERLAY_PLANES;
	SETUP_FB(fb);
	fb->id = saved_id;

	for (y = 0; y < fb->info.var.yres; ++y)
		fb_memset(fb->info.screen_base + y * fb->info.fix.line_length,
			0xff, fb->info.var.xres * fb->info.var.bits_per_pixel/8);

	CRX24_SET_OVLY_MASK(fb);
	SETUP_FB(fb);
}