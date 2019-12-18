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
struct ipuv3_channel {int dummy; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int length; int offset; } ;
struct TYPE_6__ {int length; int offset; } ;
struct TYPE_5__ {int length; int offset; } ;
struct ipu_rgb {int bits_per_pixel; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPU_FIELD_BPP ; 
 int /*<<< orphan*/  IPU_FIELD_NPB ; 
 int /*<<< orphan*/  IPU_FIELD_OFS0 ; 
 int /*<<< orphan*/  IPU_FIELD_OFS1 ; 
 int /*<<< orphan*/  IPU_FIELD_OFS2 ; 
 int /*<<< orphan*/  IPU_FIELD_OFS3 ; 
 int /*<<< orphan*/  IPU_FIELD_PFS ; 
 int /*<<< orphan*/  IPU_FIELD_WID0 ; 
 int /*<<< orphan*/  IPU_FIELD_WID1 ; 
 int /*<<< orphan*/  IPU_FIELD_WID2 ; 
 int /*<<< orphan*/  IPU_FIELD_WID3 ; 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,int) ; 

int ipu_cpmem_set_format_rgb(struct ipuv3_channel *ch,
			     const struct ipu_rgb *rgb)
{
	int bpp = 0, npb = 0, ro, go, bo, to;

	ro = rgb->bits_per_pixel - rgb->red.length - rgb->red.offset;
	go = rgb->bits_per_pixel - rgb->green.length - rgb->green.offset;
	bo = rgb->bits_per_pixel - rgb->blue.length - rgb->blue.offset;
	to = rgb->bits_per_pixel - rgb->transp.length - rgb->transp.offset;

	ipu_ch_param_write_field(ch, IPU_FIELD_WID0, rgb->red.length - 1);
	ipu_ch_param_write_field(ch, IPU_FIELD_OFS0, ro);
	ipu_ch_param_write_field(ch, IPU_FIELD_WID1, rgb->green.length - 1);
	ipu_ch_param_write_field(ch, IPU_FIELD_OFS1, go);
	ipu_ch_param_write_field(ch, IPU_FIELD_WID2, rgb->blue.length - 1);
	ipu_ch_param_write_field(ch, IPU_FIELD_OFS2, bo);

	if (rgb->transp.length) {
		ipu_ch_param_write_field(ch, IPU_FIELD_WID3,
				rgb->transp.length - 1);
		ipu_ch_param_write_field(ch, IPU_FIELD_OFS3, to);
	} else {
		ipu_ch_param_write_field(ch, IPU_FIELD_WID3, 7);
		ipu_ch_param_write_field(ch, IPU_FIELD_OFS3,
				rgb->bits_per_pixel);
	}

	switch (rgb->bits_per_pixel) {
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
	ipu_ch_param_write_field(ch, IPU_FIELD_PFS, 7); /* rgb mode */

	return 0;
}