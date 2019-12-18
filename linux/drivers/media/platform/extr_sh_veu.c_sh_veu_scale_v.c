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
struct sh_veu_dev {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (int,int) ; 
 int /*<<< orphan*/  VEU_RFCR ; 
 int /*<<< orphan*/  VEU_RFSR ; 
 int /*<<< orphan*/  sh_veu_calc_scale (struct sh_veu_dev*,int,int,int,int*,int*,int*) ; 
 int sh_veu_reg_read (struct sh_veu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_veu_reg_write (struct sh_veu_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long sh_veu_scale_v(struct sh_veu_dev *veu,
				    int size_in, int size_out, int crop_out)
{
	u32 mant, frac, value, rep;

	sh_veu_calc_scale(veu, size_in, size_out, crop_out, &mant, &frac, &rep);

	/* set scale */
	value = (sh_veu_reg_read(veu, VEU_RFCR) & ~0xffff0000) |
		(((mant << 12) | frac) << 16);

	sh_veu_reg_write(veu, VEU_RFCR, value);

	/* set clip */
	value = (sh_veu_reg_read(veu, VEU_RFSR) & ~0xffff0000) |
		(((rep << 12) | crop_out) << 16);

	sh_veu_reg_write(veu, VEU_RFSR, value);

	return ALIGN((size_in * crop_out) / size_out, 4);
}