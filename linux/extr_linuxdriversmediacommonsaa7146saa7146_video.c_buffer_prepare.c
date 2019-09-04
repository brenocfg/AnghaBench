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
struct videobuf_queue {struct file* priv_data; } ;
struct videobuf_buffer {int dummy; } ;
struct TYPE_5__ {int width; int height; int sizeimage; size_t field; scalar_t__ bytesperline; int /*<<< orphan*/  pixelformat; } ;
struct saa7146_vv {int /*<<< orphan*/  ov_fb; TYPE_2__ video_fmt; TYPE_1__* standard; } ;
struct saa7146_format {int /*<<< orphan*/  trans; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {int /*<<< orphan*/  pci; struct saa7146_vv* vv_data; } ;
struct TYPE_6__ {scalar_t__ baddr; int bsize; int width; scalar_t__ bytesperline; int height; int size; int field; scalar_t__ state; } ;
struct saa7146_buf {int /*<<< orphan*/  activate; TYPE_3__ vb; int /*<<< orphan*/ * pt; TYPE_2__* fmt; } ;
struct file {struct saa7146_fh* private_data; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_4__ {int h_max_out; int v_max_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_CAP (char*,int,...) ; 
 int /*<<< orphan*/  DEB_D (char*,...) ; 
 int EINVAL ; 
 scalar_t__ IS_PLANAR (int /*<<< orphan*/ ) ; 
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 int /*<<< orphan*/  buffer_activate ; 
 int /*<<< orphan*/  release_all_pagetables (struct saa7146_dev*,struct saa7146_buf*) ; 
 int /*<<< orphan*/  saa7146_dma_free (struct saa7146_dev*,struct videobuf_queue*,struct saa7146_buf*) ; 
 struct saa7146_format* saa7146_format_by_fourcc (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_pgtable_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int saa7146_pgtable_build (struct saa7146_dev*,struct saa7146_buf*) ; 
 int /*<<< orphan*/ * v4l2_field_names ; 
 int videobuf_iolock (struct videobuf_queue*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int buffer_prepare(struct videobuf_queue *q,
			  struct videobuf_buffer *vb, enum v4l2_field field)
{
	struct file *file = q->priv_data;
	struct saa7146_fh *fh = file->private_data;
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;
	struct saa7146_buf *buf = (struct saa7146_buf *)vb;
	int size,err = 0;

	DEB_CAP("vbuf:%p\n", vb);

	/* sanity checks */
	if (vv->video_fmt.width  < 48 ||
	    vv->video_fmt.height < 32 ||
	    vv->video_fmt.width  > vv->standard->h_max_out ||
	    vv->video_fmt.height > vv->standard->v_max_out) {
		DEB_D("w (%d) / h (%d) out of bounds\n",
		      vv->video_fmt.width, vv->video_fmt.height);
		return -EINVAL;
	}

	size = vv->video_fmt.sizeimage;
	if (0 != buf->vb.baddr && buf->vb.bsize < size) {
		DEB_D("size mismatch\n");
		return -EINVAL;
	}

	DEB_CAP("buffer_prepare [size=%dx%d,bytes=%d,fields=%s]\n",
		vv->video_fmt.width, vv->video_fmt.height,
		size, v4l2_field_names[vv->video_fmt.field]);
	if (buf->vb.width  != vv->video_fmt.width  ||
	    buf->vb.bytesperline != vv->video_fmt.bytesperline ||
	    buf->vb.height != vv->video_fmt.height ||
	    buf->vb.size   != size ||
	    buf->vb.field  != field      ||
	    buf->vb.field  != vv->video_fmt.field  ||
	    buf->fmt       != &vv->video_fmt) {
		saa7146_dma_free(dev,q,buf);
	}

	if (VIDEOBUF_NEEDS_INIT == buf->vb.state) {
		struct saa7146_format *sfmt;

		buf->vb.bytesperline  = vv->video_fmt.bytesperline;
		buf->vb.width  = vv->video_fmt.width;
		buf->vb.height = vv->video_fmt.height;
		buf->vb.size   = size;
		buf->vb.field  = field;
		buf->fmt       = &vv->video_fmt;
		buf->vb.field  = vv->video_fmt.field;

		sfmt = saa7146_format_by_fourcc(dev,buf->fmt->pixelformat);

		release_all_pagetables(dev, buf);
		if( 0 != IS_PLANAR(sfmt->trans)) {
			saa7146_pgtable_alloc(dev->pci, &buf->pt[0]);
			saa7146_pgtable_alloc(dev->pci, &buf->pt[1]);
			saa7146_pgtable_alloc(dev->pci, &buf->pt[2]);
		} else {
			saa7146_pgtable_alloc(dev->pci, &buf->pt[0]);
		}

		err = videobuf_iolock(q,&buf->vb, &vv->ov_fb);
		if (err)
			goto oops;
		err = saa7146_pgtable_build(dev,buf);
		if (err)
			goto oops;
	}
	buf->vb.state = VIDEOBUF_PREPARED;
	buf->activate = buffer_activate;

	return 0;

 oops:
	DEB_D("error out\n");
	saa7146_dma_free(dev,q,buf);

	return err;
}