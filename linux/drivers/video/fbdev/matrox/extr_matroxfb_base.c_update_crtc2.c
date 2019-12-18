#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ length; } ;
struct TYPE_10__ {scalar_t__ bits_per_pixel; scalar_t__ xres_virtual; TYPE_2__ green; } ;
struct TYPE_11__ {TYPE_3__ var; } ;
struct matroxfb_dh_fb_info {int /*<<< orphan*/  interlaced; TYPE_4__ fbcon; } ;
struct TYPE_12__ {scalar_t__ length; } ;
struct TYPE_13__ {scalar_t__ bits_per_pixel; scalar_t__ xres_virtual; TYPE_5__ green; } ;
struct TYPE_14__ {TYPE_6__ var; } ;
struct TYPE_8__ {struct matroxfb_dh_fb_info* info; } ;
struct matrox_fb_info {TYPE_7__ fbcon; TYPE_1__ crtc2; } ;

/* Variables and functions */
 int /*<<< orphan*/  mga_outl (int,unsigned int) ; 

__attribute__((used)) static void update_crtc2(struct matrox_fb_info *minfo, unsigned int pos)
{
	struct matroxfb_dh_fb_info *info = minfo->crtc2.info;

	/* Make sure that displays are compatible */
	if (info && (info->fbcon.var.bits_per_pixel == minfo->fbcon.var.bits_per_pixel)
		 && (info->fbcon.var.xres_virtual == minfo->fbcon.var.xres_virtual)
		 && (info->fbcon.var.green.length == minfo->fbcon.var.green.length)
		 ) {
		switch (minfo->fbcon.var.bits_per_pixel) {
			case 16:
			case 32:
				pos = pos * 8;
				if (info->interlaced) {
					mga_outl(0x3C2C, pos);
					mga_outl(0x3C28, pos + minfo->fbcon.var.xres_virtual * minfo->fbcon.var.bits_per_pixel / 8);
				} else {
					mga_outl(0x3C28, pos);
				}
				break;
		}
	}
}