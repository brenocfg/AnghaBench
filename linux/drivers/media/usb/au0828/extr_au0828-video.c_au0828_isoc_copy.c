#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {int status; int number_of_packets; unsigned char* transfer_buffer; TYPE_2__* iso_frame_desc; struct au0828_dmaqueue* context; } ;
struct au0828_dmaqueue {scalar_t__ pos; } ;
struct TYPE_4__ {struct au0828_buffer* vbi_buf; struct au0828_buffer* buf; } ;
struct au0828_dev {int max_pkt_size; unsigned int vbi_read; int vbi_width; int vbi_height; int /*<<< orphan*/  vbi_timeout; scalar_t__ vbi_timeout_running; int /*<<< orphan*/  vid_timeout; scalar_t__ vid_timeout_running; TYPE_1__ isoc_ctl; int /*<<< orphan*/  dev_state; struct au0828_dmaqueue vbiq; } ;
struct TYPE_6__ {int /*<<< orphan*/  vb2_buf; } ;
struct au0828_buffer {int top_field; TYPE_3__ vb; } ;
struct TYPE_5__ {int status; int actual_length; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  DEV_MISCONFIGURED ; 
 int ENOENT ; 
 int EPROTO ; 
 int HZ ; 
 int /*<<< orphan*/  au0828_copy_vbi (struct au0828_dev*,struct au0828_dmaqueue*,struct au0828_buffer*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  au0828_copy_video (struct au0828_dev*,struct au0828_dmaqueue*,struct au0828_buffer*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  au0828_isocdbg (char*,...) ; 
 int /*<<< orphan*/  buffer_filled (struct au0828_dev*,struct au0828_dmaqueue*,struct au0828_buffer*) ; 
 int /*<<< orphan*/  get_next_buf (struct au0828_dmaqueue*,struct au0828_buffer**) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  print_err_status (struct au0828_dev*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbi_get_next_buf (struct au0828_dmaqueue*,struct au0828_buffer**) ; 

__attribute__((used)) static inline int au0828_isoc_copy(struct au0828_dev *dev, struct urb *urb)
{
	struct au0828_buffer    *buf;
	struct au0828_buffer    *vbi_buf;
	struct au0828_dmaqueue  *dma_q = urb->context;
	struct au0828_dmaqueue  *vbi_dma_q = &dev->vbiq;
	unsigned char *outp = NULL;
	unsigned char *vbioutp = NULL;
	int i, len = 0, rc = 1;
	unsigned char *p;
	unsigned char fbyte;
	unsigned int vbi_field_size;
	unsigned int remain, lencopy;

	if (!dev)
		return 0;

	if (test_bit(DEV_DISCONNECTED, &dev->dev_state) ||
	    test_bit(DEV_MISCONFIGURED, &dev->dev_state))
		return 0;

	if (urb->status < 0) {
		print_err_status(dev, -1, urb->status);
		if (urb->status == -ENOENT)
			return 0;
	}

	buf = dev->isoc_ctl.buf;
	if (buf != NULL)
		outp = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	vbi_buf = dev->isoc_ctl.vbi_buf;
	if (vbi_buf != NULL)
		vbioutp = vb2_plane_vaddr(&vbi_buf->vb.vb2_buf, 0);

	for (i = 0; i < urb->number_of_packets; i++) {
		int status = urb->iso_frame_desc[i].status;

		if (status < 0) {
			print_err_status(dev, i, status);
			if (urb->iso_frame_desc[i].status != -EPROTO)
				continue;
		}

		if (urb->iso_frame_desc[i].actual_length <= 0)
			continue;

		if (urb->iso_frame_desc[i].actual_length >
						dev->max_pkt_size) {
			au0828_isocdbg("packet bigger than packet size");
			continue;
		}

		p = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		fbyte = p[0];
		len = urb->iso_frame_desc[i].actual_length - 4;
		p += 4;

		if (fbyte & 0x80) {
			len -= 4;
			p += 4;
			au0828_isocdbg("Video frame %s\n",
				       (fbyte & 0x40) ? "odd" : "even");
			if (fbyte & 0x40) {
				/* VBI */
				if (vbi_buf != NULL)
					buffer_filled(dev, vbi_dma_q, vbi_buf);
				vbi_get_next_buf(vbi_dma_q, &vbi_buf);
				if (vbi_buf == NULL)
					vbioutp = NULL;
				else
					vbioutp = vb2_plane_vaddr(
						&vbi_buf->vb.vb2_buf, 0);

				/* Video */
				if (buf != NULL)
					buffer_filled(dev, dma_q, buf);
				get_next_buf(dma_q, &buf);
				if (buf == NULL)
					outp = NULL;
				else
					outp = vb2_plane_vaddr(
						&buf->vb.vb2_buf, 0);

				/* As long as isoc traffic is arriving, keep
				   resetting the timer */
				if (dev->vid_timeout_running)
					mod_timer(&dev->vid_timeout,
						  jiffies + (HZ / 10));
				if (dev->vbi_timeout_running)
					mod_timer(&dev->vbi_timeout,
						  jiffies + (HZ / 10));
			}

			if (buf != NULL) {
				if (fbyte & 0x40)
					buf->top_field = 1;
				else
					buf->top_field = 0;
			}

			if (vbi_buf != NULL) {
				if (fbyte & 0x40)
					vbi_buf->top_field = 1;
				else
					vbi_buf->top_field = 0;
			}

			dev->vbi_read = 0;
			vbi_dma_q->pos = 0;
			dma_q->pos = 0;
		}

		vbi_field_size = dev->vbi_width * dev->vbi_height * 2;
		if (dev->vbi_read < vbi_field_size) {
			remain  = vbi_field_size - dev->vbi_read;
			if (len < remain)
				lencopy = len;
			else
				lencopy = remain;

			if (vbi_buf != NULL)
				au0828_copy_vbi(dev, vbi_dma_q, vbi_buf, p,
						vbioutp, len);

			len -= lencopy;
			p += lencopy;
			dev->vbi_read += lencopy;
		}

		if (dev->vbi_read >= vbi_field_size && buf != NULL)
			au0828_copy_video(dev, dma_q, buf, p, outp, len);
	}
	return rc;
}