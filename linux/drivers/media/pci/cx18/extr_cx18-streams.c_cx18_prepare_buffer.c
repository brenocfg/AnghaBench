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
typedef  scalar_t__ u32 ;
struct videobuf_queue {int dummy; } ;
struct TYPE_2__ {unsigned int size; scalar_t__ baddr; unsigned int bsize; unsigned int width; unsigned int height; int field; scalar_t__ state; } ;
struct cx18_videobuf_buffer {scalar_t__ tvnorm; TYPE_1__ vb; scalar_t__ bytes_used; } ;
struct cx18_stream {scalar_t__ pixelformat; unsigned int vb_bytes_per_frame; struct cx18* cx; } ;
struct cx18 {scalar_t__ std; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_PIX_FMT_HM12 ; 
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 int /*<<< orphan*/  cx18_dma_free (struct videobuf_queue*,struct cx18_stream*,struct cx18_videobuf_buffer*) ; 
 int videobuf_iolock (struct videobuf_queue*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx18_prepare_buffer(struct videobuf_queue *q,
	struct cx18_stream *s,
	struct cx18_videobuf_buffer *buf,
	u32 pixelformat,
	unsigned int width, unsigned int height,
	enum v4l2_field field)
{
	struct cx18 *cx = s->cx;
	int rc = 0;

	/* check settings */
	buf->bytes_used = 0;

	if ((width  < 48) || (height < 32))
		return -EINVAL;

	buf->vb.size = (width * height * 2);
	if ((buf->vb.baddr != 0) && (buf->vb.bsize < buf->vb.size))
		return -EINVAL;

	/* alloc + fill struct (if changed) */
	if (buf->vb.width != width || buf->vb.height != height ||
	    buf->vb.field != field || s->pixelformat != pixelformat ||
	    buf->tvnorm != cx->std) {

		buf->vb.width  = width;
		buf->vb.height = height;
		buf->vb.field  = field;
		buf->tvnorm    = cx->std;
		s->pixelformat = pixelformat;

		/* HM12 YUV size is (Y=(h*720) + UV=(h*(720/2)))
		   UYUV YUV size is (Y=(h*720) + UV=(h*(720))) */
		if (s->pixelformat == V4L2_PIX_FMT_HM12)
			s->vb_bytes_per_frame = height * 720 * 3 / 2;
		else
			s->vb_bytes_per_frame = height * 720 * 2;
		cx18_dma_free(q, s, buf);
	}

	if ((buf->vb.baddr != 0) && (buf->vb.bsize < buf->vb.size))
		return -EINVAL;

	if (buf->vb.field == 0)
		buf->vb.field = V4L2_FIELD_INTERLACED;

	if (VIDEOBUF_NEEDS_INIT == buf->vb.state) {
		buf->vb.width  = width;
		buf->vb.height = height;
		buf->vb.field  = field;
		buf->tvnorm    = cx->std;
		s->pixelformat = pixelformat;

		/* HM12 YUV size is (Y=(h*720) + UV=(h*(720/2)))
		   UYUV YUV size is (Y=(h*720) + UV=(h*(720))) */
		if (s->pixelformat == V4L2_PIX_FMT_HM12)
			s->vb_bytes_per_frame = height * 720 * 3 / 2;
		else
			s->vb_bytes_per_frame = height * 720 * 2;
		rc = videobuf_iolock(q, &buf->vb, NULL);
		if (rc != 0)
			goto fail;
	}
	buf->vb.state = VIDEOBUF_PREPARED;
	return 0;

fail:
	cx18_dma_free(q, s, buf);
	return rc;

}