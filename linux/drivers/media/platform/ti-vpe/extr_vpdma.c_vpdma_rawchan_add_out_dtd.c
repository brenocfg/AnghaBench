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
typedef  int u32 ;
struct vpdma_dtd {int start_addr; scalar_t__ client_attr1; scalar_t__ client_attr0; int /*<<< orphan*/  max_width_height; int /*<<< orphan*/  desc_write_addr; int /*<<< orphan*/  pkt_ctl; scalar_t__ w1; int /*<<< orphan*/  type_ctl_stride; } ;
struct TYPE_2__ {void* addr; int size; } ;
struct vpdma_desc_list {struct vpdma_dtd* next; TYPE_1__ buf; } ;
struct vpdma_data_format {int depth; scalar_t__ type; scalar_t__ data_type; } ;
struct v4l2_rect {int height; int top; int left; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_C420 ; 
 int /*<<< orphan*/  DTD_DIR_OUT ; 
 int VPDMA_DATA_EVEN_LINE_SKIP ; 
 scalar_t__ VPDMA_DATA_FMT_TYPE_YUV ; 
 int VPDMA_DATA_FRAME_1D ; 
 int VPDMA_DATA_MODE_TILED ; 
 int VPDMA_DATA_ODD_LINE_SKIP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dtd_desc_write_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtd_max_width_height (int,int) ; 
 int /*<<< orphan*/  dtd_pkt_ctl (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dtd_type_ctl_stride (scalar_t__,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dump_dtd (struct vpdma_dtd*) ; 

void vpdma_rawchan_add_out_dtd(struct vpdma_desc_list *list, int width,
		int stride, const struct v4l2_rect *c_rect,
		const struct vpdma_data_format *fmt, dma_addr_t dma_addr,
		int max_w, int max_h, int raw_vpdma_chan, u32 flags)
{
	int priority = 0;
	int field = 0;
	int notify = 1;
	int channel, next_chan;
	struct v4l2_rect rect = *c_rect;
	int depth = fmt->depth;
	struct vpdma_dtd *dtd;

	channel = next_chan = raw_vpdma_chan;

	if (fmt->type == VPDMA_DATA_FMT_TYPE_YUV &&
			fmt->data_type == DATA_TYPE_C420) {
		rect.height >>= 1;
		rect.top >>= 1;
		depth = 8;
	}

	dma_addr += rect.top * stride + (rect.left * depth >> 3);

	dtd = list->next;
	WARN_ON((void *)(dtd + 1) > (list->buf.addr + list->buf.size));

	dtd->type_ctl_stride = dtd_type_ctl_stride(fmt->data_type,
					notify,
					field,
					!!(flags & VPDMA_DATA_FRAME_1D),
					!!(flags & VPDMA_DATA_EVEN_LINE_SKIP),
					!!(flags & VPDMA_DATA_ODD_LINE_SKIP),
					stride);
	dtd->w1 = 0;
	dtd->start_addr = (u32) dma_addr;
	dtd->pkt_ctl = dtd_pkt_ctl(!!(flags & VPDMA_DATA_MODE_TILED),
				DTD_DIR_OUT, channel, priority, next_chan);
	dtd->desc_write_addr = dtd_desc_write_addr(0, 0, 0, 0);
	dtd->max_width_height = dtd_max_width_height(max_w, max_h);
	dtd->client_attr0 = 0;
	dtd->client_attr1 = 0;

	list->next = dtd + 1;

	dump_dtd(dtd);
}