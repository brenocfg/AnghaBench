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
struct vivid_dev {int* vbi_out_have_cc; int vbi_out_have_wss; int std_out; int /*<<< orphan*/ * vbi_out_wss; int /*<<< orphan*/ ** vbi_out_cc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct vivid_buffer {TYPE_1__ vb; } ;
struct v4l2_sliced_vbi_data {int id; int line; int /*<<< orphan*/ * data; int /*<<< orphan*/  field; } ;

/* Variables and functions */
#define  V4L2_SLICED_CAPTION_525 129 
#define  V4L2_SLICED_WSS_625 128 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int vb2_get_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct v4l2_sliced_vbi_data* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vivid_sliced_vbi_out_process(struct vivid_dev *dev,
		struct vivid_buffer *buf)
{
	struct v4l2_sliced_vbi_data *vbi =
		vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	unsigned elems =
		vb2_get_plane_payload(&buf->vb.vb2_buf, 0) / sizeof(*vbi);

	dev->vbi_out_have_cc[0] = false;
	dev->vbi_out_have_cc[1] = false;
	dev->vbi_out_have_wss = false;
	while (elems--) {
		switch (vbi->id) {
		case V4L2_SLICED_CAPTION_525:
			if ((dev->std_out & V4L2_STD_525_60) && vbi->line == 21) {
				dev->vbi_out_have_cc[!!vbi->field] = true;
				dev->vbi_out_cc[!!vbi->field][0] = vbi->data[0];
				dev->vbi_out_cc[!!vbi->field][1] = vbi->data[1];
			}
			break;
		case V4L2_SLICED_WSS_625:
			if ((dev->std_out & V4L2_STD_625_50) &&
			    vbi->field == 0 && vbi->line == 23) {
				dev->vbi_out_have_wss = true;
				dev->vbi_out_wss[0] = vbi->data[0];
				dev->vbi_out_wss[1] = vbi->data[1];
			}
			break;
		}
		vbi++;
	}
}