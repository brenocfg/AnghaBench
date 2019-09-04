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
struct ipuv3_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPU_FIELD_BPP ; 
 int /*<<< orphan*/  IPU_FIELD_NPB ; 
 int /*<<< orphan*/  IPU_FIELD_PFS ; 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,int) ; 

int ipu_cpmem_set_format_passthrough(struct ipuv3_channel *ch, int width)
{
	int bpp = 0, npb = 0;

	switch (width) {
	case 32:
		bpp = 0;
		npb = 15;
		break;
	case 24:
		bpp = 1;
		npb = 19;
		break;
	case 16:
		bpp = 3;
		npb = 31;
		break;
	case 8:
		bpp = 5;
		npb = 63;
		break;
	default:
		return -EINVAL;
	}

	ipu_ch_param_write_field(ch, IPU_FIELD_BPP, bpp);
	ipu_ch_param_write_field(ch, IPU_FIELD_NPB, npb);
	ipu_ch_param_write_field(ch, IPU_FIELD_PFS, 6); /* raw mode */

	return 0;
}