#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int num_planes; } ;
struct vb2_v4l2_buffer {int field; TYPE_2__ vb2_buf; } ;
struct TYPE_3__ {int height; } ;
struct fdp1_q_data {int stride_y; int stride_c; int vsize; TYPE_1__ format; } ;
struct fdp1_field_buffer {int last_field; int* addrs; int field; struct vb2_v4l2_buffer* vb; } ;
struct fdp1_buffer {struct fdp1_field_buffer* fields; } ;

/* Variables and functions */
 void* V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_HAS_BOTH (int) ; 
#define  V4L2_FIELD_INTERLACED 132 
#define  V4L2_FIELD_INTERLACED_BT 131 
#define  V4L2_FIELD_INTERLACED_TB 130 
#define  V4L2_FIELD_SEQ_BT 129 
#define  V4L2_FIELD_SEQ_TB 128 
 void* V4L2_FIELD_TOP ; 
 struct fdp1_buffer* to_fdp1_buffer (struct vb2_v4l2_buffer*) ; 
 int vb2_dma_contig_plane_dma_addr (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void fdp1_buf_prepare_field(struct fdp1_q_data *q_data,
				   struct vb2_v4l2_buffer *vbuf,
				   unsigned int field_num)
{
	struct fdp1_buffer *buf = to_fdp1_buffer(vbuf);
	struct fdp1_field_buffer *fbuf = &buf->fields[field_num];
	unsigned int num_fields;
	unsigned int i;

	num_fields = V4L2_FIELD_HAS_BOTH(vbuf->field) ? 2 : 1;

	fbuf->vb = vbuf;
	fbuf->last_field = (field_num + 1) == num_fields;

	for (i = 0; i < vbuf->vb2_buf.num_planes; ++i)
		fbuf->addrs[i] = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, i);

	switch (vbuf->field) {
	case V4L2_FIELD_INTERLACED:
		/*
		 * Interlaced means bottom-top for 60Hz TV standards (NTSC) and
		 * top-bottom for 50Hz. As TV standards are not applicable to
		 * the mem-to-mem API, use the height as a heuristic.
		 */
		fbuf->field = (q_data->format.height < 576) == field_num
			    ? V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM;
		break;
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_SEQ_TB:
		fbuf->field = field_num ? V4L2_FIELD_BOTTOM : V4L2_FIELD_TOP;
		break;
	case V4L2_FIELD_INTERLACED_BT:
	case V4L2_FIELD_SEQ_BT:
		fbuf->field = field_num ? V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM;
		break;
	default:
		fbuf->field = vbuf->field;
		break;
	}

	/* Buffer is completed */
	if (!field_num)
		return;

	/* Adjust buffer addresses for second field */
	switch (vbuf->field) {
	case V4L2_FIELD_INTERLACED:
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_INTERLACED_BT:
		for (i = 0; i < vbuf->vb2_buf.num_planes; i++)
			fbuf->addrs[i] +=
				(i == 0 ? q_data->stride_y : q_data->stride_c);
		break;
	case V4L2_FIELD_SEQ_TB:
	case V4L2_FIELD_SEQ_BT:
		for (i = 0; i < vbuf->vb2_buf.num_planes; i++)
			fbuf->addrs[i] += q_data->vsize *
				(i == 0 ? q_data->stride_y : q_data->stride_c);
		break;
	}
}