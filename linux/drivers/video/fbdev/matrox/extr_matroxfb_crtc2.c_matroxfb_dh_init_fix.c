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
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  len_usable; int /*<<< orphan*/  base; } ;
struct fb_fix_screeninfo {int ypanstep; int xpanstep; scalar_t__ accel; int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio_start; scalar_t__ ywrapstep; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {struct fb_fix_screeninfo fix; } ;
struct matroxfb_dh_fb_info {TYPE_2__ mmio; TYPE_1__ video; TYPE_3__ fbcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void matroxfb_dh_init_fix(struct matroxfb_dh_fb_info *m2info)
{
	struct fb_fix_screeninfo *fix = &m2info->fbcon.fix;

	strcpy(fix->id, "MATROX DH");

	fix->smem_start = m2info->video.base;
	fix->smem_len = m2info->video.len_usable;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->xpanstep = 8;	/* TBD */
	fix->mmio_start = m2info->mmio.base;
	fix->mmio_len = m2info->mmio.len;
	fix->accel = 0;		/* no accel... */
}