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
 int /*<<< orphan*/  IPU_FIELD_BPP ; 
 int /*<<< orphan*/  IPU_FIELD_NPB ; 
 int /*<<< orphan*/  IPU_FIELD_PFS ; 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,int) ; 

void ipu_cpmem_set_yuv_interleaved(struct ipuv3_channel *ch, u32 pixel_format)
{
	switch (pixel_format) {
	case V4L2_PIX_FMT_UYVY:
		ipu_ch_param_write_field(ch, IPU_FIELD_BPP, 3); /* bits/pixel */
		ipu_ch_param_write_field(ch, IPU_FIELD_PFS, 0xA);/* pix fmt */
		ipu_ch_param_write_field(ch, IPU_FIELD_NPB, 31);/* burst size */
		break;
	case V4L2_PIX_FMT_YUYV:
		ipu_ch_param_write_field(ch, IPU_FIELD_BPP, 3); /* bits/pixel */
		ipu_ch_param_write_field(ch, IPU_FIELD_PFS, 0x8);/* pix fmt */
		ipu_ch_param_write_field(ch, IPU_FIELD_NPB, 31);/* burst size */
		break;
	}
}