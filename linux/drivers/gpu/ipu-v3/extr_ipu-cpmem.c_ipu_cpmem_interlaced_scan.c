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
struct ipuv3_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_FIELD_ILO ; 
 int /*<<< orphan*/  IPU_FIELD_SLUV ; 
 int /*<<< orphan*/  IPU_FIELD_SLY ; 
 int /*<<< orphan*/  IPU_FIELD_SO ; 
#define  V4L2_PIX_FMT_NV12 132 
#define  V4L2_PIX_FMT_NV16 131 
#define  V4L2_PIX_FMT_YUV420 130 
#define  V4L2_PIX_FMT_YUV422P 129 
#define  V4L2_PIX_FMT_YVU420 128 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,int) ; 

void ipu_cpmem_interlaced_scan(struct ipuv3_channel *ch, int stride,
			       u32 pixelformat)
{
	u32 ilo, sly, sluv;

	if (stride < 0) {
		stride = -stride;
		ilo = 0x100000 - (stride / 8);
	} else {
		ilo = stride / 8;
	}

	sly = (stride * 2) - 1;

	switch (pixelformat) {
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
		sluv = stride / 2 - 1;
		break;
	case V4L2_PIX_FMT_NV12:
		sluv = stride - 1;
		break;
	case V4L2_PIX_FMT_YUV422P:
		sluv = stride - 1;
		break;
	case V4L2_PIX_FMT_NV16:
		sluv = stride * 2 - 1;
		break;
	default:
		sluv = 0;
		break;
	}

	ipu_ch_param_write_field(ch, IPU_FIELD_SO, 1);
	ipu_ch_param_write_field(ch, IPU_FIELD_ILO, ilo);
	ipu_ch_param_write_field(ch, IPU_FIELD_SLY, sly);
	if (sluv)
		ipu_ch_param_write_field(ch, IPU_FIELD_SLUV, sluv);
}