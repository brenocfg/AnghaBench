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
struct sh_veu_dev {scalar_t__ is_2h; } ;

/* Variables and functions */

__attribute__((used)) static void sh_veu_calc_scale(struct sh_veu_dev *veu,
			      int size_in, int size_out, int crop_out,
			      u32 *mant, u32 *frac, u32 *rep)
{
	u32 fixpoint;

	/* calculate FRAC and MANT */
	*rep = *mant = *frac = 0;

	if (size_in == size_out) {
		if (crop_out != size_out)
			*mant = 1; /* needed for cropping */
		return;
	}

	/* VEU2H special upscale */
	if (veu->is_2h && size_out > size_in) {
		u32 fixpoint = (4096 * size_in) / size_out;
		*mant = fixpoint / 4096;
		*frac = (fixpoint - (*mant * 4096)) & ~0x07;

		switch (*frac) {
		case 0x800:
			*rep = 1;
			break;
		case 0x400:
			*rep = 3;
			break;
		case 0x200:
			*rep = 7;
			break;
		}
		if (*rep)
			return;
	}

	fixpoint = (4096 * (size_in - 1)) / (size_out + 1);
	*mant = fixpoint / 4096;
	*frac = fixpoint - (*mant * 4096);

	if (*frac & 0x07) {
		/*
		 * FIXME: do we really have to round down twice in the
		 * up-scaling case?
		 */
		*frac &= ~0x07;
		if (size_out > size_in)
			*frac -= 8; /* round down if scaling up */
		else
			*frac += 8; /* round up if scaling down */
	}
}