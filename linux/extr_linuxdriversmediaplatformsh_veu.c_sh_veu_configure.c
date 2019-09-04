#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_8__ {int bytesperline; TYPE_3__ frame; } ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_6__ {TYPE_1__ frame; } ;
struct sh_veu_dev {scalar_t__ is_2h; TYPE_4__ vfmt_out; TYPE_2__ vfmt_in; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  VEU_BSRR ; 
 int /*<<< orphan*/  VEU_BSSR ; 
 int /*<<< orphan*/  VEU_COFFR ; 
 int /*<<< orphan*/  VEU_DACR ; 
 int /*<<< orphan*/  VEU_EDWR ; 
 int /*<<< orphan*/  VEU_MCR00 ; 
 int /*<<< orphan*/  VEU_MCR01 ; 
 int /*<<< orphan*/  VEU_MCR02 ; 
 int /*<<< orphan*/  VEU_MCR10 ; 
 int /*<<< orphan*/  VEU_MCR11 ; 
 int /*<<< orphan*/  VEU_MCR12 ; 
 int /*<<< orphan*/  VEU_MCR20 ; 
 int /*<<< orphan*/  VEU_MCR21 ; 
 int /*<<< orphan*/  VEU_MCR22 ; 
 int /*<<< orphan*/  VEU_SSR ; 
 int /*<<< orphan*/  VEU_SWPR ; 
 int /*<<< orphan*/  VEU_SWR ; 
 int /*<<< orphan*/  VEU_TRCR ; 
 int /*<<< orphan*/  sh_veu_reg_write (struct sh_veu_dev*,int /*<<< orphan*/ ,int) ; 
 int sh_veu_scale_h (struct sh_veu_dev*,int,int,int) ; 
 int sh_veu_scale_v (struct sh_veu_dev*,int,int,int) ; 

__attribute__((used)) static void sh_veu_configure(struct sh_veu_dev *veu)
{
	u32 src_width, src_stride, src_height;
	u32 dst_width, dst_stride, dst_height;
	u32 real_w, real_h;

	/* reset VEU */
	sh_veu_reg_write(veu, VEU_BSRR, 0x100);

	src_width = veu->vfmt_in.frame.width;
	src_height = veu->vfmt_in.frame.height;
	src_stride = ALIGN(veu->vfmt_in.frame.width, 16);

	dst_width = real_w = veu->vfmt_out.frame.width;
	dst_height = real_h = veu->vfmt_out.frame.height;
	/* Datasheet is unclear - whether it's always number of bytes or not */
	dst_stride = veu->vfmt_out.bytesperline;

	/*
	 * So far real_w == dst_width && real_h == dst_height, but it wasn't
	 * necessarily the case in the original vidix driver, so, it may change
	 * here in the future too.
	 */
	src_width = sh_veu_scale_h(veu, src_width, real_w, dst_width);
	src_height = sh_veu_scale_v(veu, src_height, real_h, dst_height);

	sh_veu_reg_write(veu, VEU_SWR, src_stride);
	sh_veu_reg_write(veu, VEU_SSR, src_width | (src_height << 16));
	sh_veu_reg_write(veu, VEU_BSSR, 0); /* not using bundle mode */

	sh_veu_reg_write(veu, VEU_EDWR, dst_stride);
	sh_veu_reg_write(veu, VEU_DACR, 0); /* unused for RGB */

	sh_veu_reg_write(veu, VEU_SWPR, 0x67);
	sh_veu_reg_write(veu, VEU_TRCR, (6 << 16) | (0 << 14) | 2 | 4);

	if (veu->is_2h) {
		sh_veu_reg_write(veu, VEU_MCR00, 0x0cc5);
		sh_veu_reg_write(veu, VEU_MCR01, 0x0950);
		sh_veu_reg_write(veu, VEU_MCR02, 0x0000);

		sh_veu_reg_write(veu, VEU_MCR10, 0x397f);
		sh_veu_reg_write(veu, VEU_MCR11, 0x0950);
		sh_veu_reg_write(veu, VEU_MCR12, 0x3ccd);

		sh_veu_reg_write(veu, VEU_MCR20, 0x0000);
		sh_veu_reg_write(veu, VEU_MCR21, 0x0950);
		sh_veu_reg_write(veu, VEU_MCR22, 0x1023);

		sh_veu_reg_write(veu, VEU_COFFR, 0x00800010);
	}
}