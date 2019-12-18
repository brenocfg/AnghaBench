#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vivid_vbi_gen_data {TYPE_1__* data; } ;
struct vivid_dev {int* std_cap; size_t input; int* vbi_out_wss; int** vbi_out_cc; scalar_t__* vbi_out_have_cc; scalar_t__ loop_video; int /*<<< orphan*/  tpg; scalar_t__ vbi_out_have_wss; struct vivid_vbi_gen_data vbi_gen; } ;
struct TYPE_2__ {int* data; scalar_t__ id; } ;

/* Variables and functions */
#define  TPG_VIDEO_ASPECT_14X9_CENTRE 131 
#define  TPG_VIDEO_ASPECT_16X9_ANAMORPHIC 130 
#define  TPG_VIDEO_ASPECT_16X9_CENTRE 129 
#define  TPG_VIDEO_ASPECT_4X3 128 
 int V4L2_STD_525_60 ; 
 int tpg_g_video_aspect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vivid_vbi_gen_sliced (struct vivid_vbi_gen_data*,int,unsigned int) ; 

__attribute__((used)) static void vivid_sliced_vbi_cap_fill(struct vivid_dev *dev, unsigned seqnr)
{
	struct vivid_vbi_gen_data *vbi_gen = &dev->vbi_gen;
	bool is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;

	vivid_vbi_gen_sliced(vbi_gen, is_60hz, seqnr);

	if (!is_60hz) {
		if (dev->loop_video) {
			if (dev->vbi_out_have_wss) {
				vbi_gen->data[12].data[0] = dev->vbi_out_wss[0];
				vbi_gen->data[12].data[1] = dev->vbi_out_wss[1];
			} else {
				vbi_gen->data[12].id = 0;
			}
		} else {
			switch (tpg_g_video_aspect(&dev->tpg)) {
			case TPG_VIDEO_ASPECT_14X9_CENTRE:
				vbi_gen->data[12].data[0] = 0x01;
				break;
			case TPG_VIDEO_ASPECT_16X9_CENTRE:
				vbi_gen->data[12].data[0] = 0x0b;
				break;
			case TPG_VIDEO_ASPECT_16X9_ANAMORPHIC:
				vbi_gen->data[12].data[0] = 0x07;
				break;
			case TPG_VIDEO_ASPECT_4X3:
			default:
				vbi_gen->data[12].data[0] = 0x08;
				break;
			}
		}
	} else if (dev->loop_video && is_60hz) {
		if (dev->vbi_out_have_cc[0]) {
			vbi_gen->data[0].data[0] = dev->vbi_out_cc[0][0];
			vbi_gen->data[0].data[1] = dev->vbi_out_cc[0][1];
		} else {
			vbi_gen->data[0].id = 0;
		}
		if (dev->vbi_out_have_cc[1]) {
			vbi_gen->data[1].data[0] = dev->vbi_out_cc[1][0];
			vbi_gen->data[1].data[1] = dev->vbi_out_cc[1][1];
		} else {
			vbi_gen->data[1].id = 0;
		}
	}
}