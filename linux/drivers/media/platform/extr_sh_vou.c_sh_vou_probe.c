#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct video_device {struct vb2_queue* queue; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  tvnorms; } ;
struct vb2_queue {int io_modes; int buf_struct_size; int min_buffers_needed; TYPE_1__* dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct sh_vou_device* drv_priv; int /*<<< orphan*/  type; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct sh_vou_pdata {scalar_t__ bus_fmt; int /*<<< orphan*/  board_info; int /*<<< orphan*/  i2c_adap; } ;
struct sh_vou_device {int pix_idx; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  buf_list; int /*<<< orphan*/  fop_lock; struct vb2_queue queue; struct video_device vdev; int /*<<< orphan*/  base; int /*<<< orphan*/  std; struct v4l2_pix_format pix; struct v4l2_rect rect; int /*<<< orphan*/  status; struct sh_vou_pdata* pdata; int /*<<< orphan*/  lock; } ;
struct sh_vou_buffer {int dummy; } ;
struct resource {int dummy; } ;
struct TYPE_9__ {struct sh_vou_pdata* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SH_VOU_BUS_8BIT ; 
 int /*<<< orphan*/  SH_VOU_INITIALISING ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV16 ; 
 int /*<<< orphan*/  V4L2_STD_NTSC_M ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_WRITE ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int VOU_MAX_IMAGE_WIDTH ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct sh_vou_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sh_vou_device*) ; 
 struct i2c_adapter* i2c_get_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_resume (TYPE_1__*) ; 
 int sh_vou_hw_init (struct sh_vou_device*) ; 
 int /*<<< orphan*/  sh_vou_isr ; 
 int /*<<< orphan*/  sh_vou_qops ; 
 struct video_device sh_vou_video_template ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* v4l2_i2c_new_subdev_board (int /*<<< orphan*/ *,struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct sh_vou_device*) ; 

__attribute__((used)) static int sh_vou_probe(struct platform_device *pdev)
{
	struct sh_vou_pdata *vou_pdata = pdev->dev.platform_data;
	struct v4l2_rect *rect;
	struct v4l2_pix_format *pix;
	struct i2c_adapter *i2c_adap;
	struct video_device *vdev;
	struct sh_vou_device *vou_dev;
	struct resource *reg_res;
	struct v4l2_subdev *subdev;
	struct vb2_queue *q;
	int irq, ret;

	reg_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platform_get_irq(pdev, 0);

	if (!vou_pdata || !reg_res || irq <= 0) {
		dev_err(&pdev->dev, "Insufficient VOU platform information.\n");
		return -ENODEV;
	}

	vou_dev = devm_kzalloc(&pdev->dev, sizeof(*vou_dev), GFP_KERNEL);
	if (!vou_dev)
		return -ENOMEM;

	INIT_LIST_HEAD(&vou_dev->buf_list);
	spin_lock_init(&vou_dev->lock);
	mutex_init(&vou_dev->fop_lock);
	vou_dev->pdata = vou_pdata;
	vou_dev->status = SH_VOU_INITIALISING;
	vou_dev->pix_idx = 1;

	rect = &vou_dev->rect;
	pix = &vou_dev->pix;

	/* Fill in defaults */
	vou_dev->std		= V4L2_STD_NTSC_M;
	rect->left		= 0;
	rect->top		= 0;
	rect->width		= VOU_MAX_IMAGE_WIDTH;
	rect->height		= 480;
	pix->width		= VOU_MAX_IMAGE_WIDTH;
	pix->height		= 480;
	pix->pixelformat	= V4L2_PIX_FMT_NV16;
	pix->field		= V4L2_FIELD_INTERLACED;
	pix->bytesperline	= VOU_MAX_IMAGE_WIDTH;
	pix->sizeimage		= VOU_MAX_IMAGE_WIDTH * 2 * 480;
	pix->colorspace		= V4L2_COLORSPACE_SMPTE170M;

	vou_dev->base = devm_ioremap_resource(&pdev->dev, reg_res);
	if (IS_ERR(vou_dev->base))
		return PTR_ERR(vou_dev->base);

	ret = devm_request_irq(&pdev->dev, irq, sh_vou_isr, 0, "vou", vou_dev);
	if (ret < 0)
		return ret;

	ret = v4l2_device_register(&pdev->dev, &vou_dev->v4l2_dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Error registering v4l2 device\n");
		return ret;
	}

	vdev = &vou_dev->vdev;
	*vdev = sh_vou_video_template;
	if (vou_pdata->bus_fmt == SH_VOU_BUS_8BIT)
		vdev->tvnorms |= V4L2_STD_PAL;
	vdev->v4l2_dev = &vou_dev->v4l2_dev;
	vdev->release = video_device_release_empty;
	vdev->lock = &vou_dev->fop_lock;

	video_set_drvdata(vdev, vou_dev);

	/* Initialize the vb2 queue */
	q = &vou_dev->queue;
	q->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_WRITE;
	q->drv_priv = vou_dev;
	q->buf_struct_size = sizeof(struct sh_vou_buffer);
	q->ops = &sh_vou_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->lock = &vou_dev->fop_lock;
	q->dev = &pdev->dev;
	ret = vb2_queue_init(q);
	if (ret)
		goto ei2cgadap;

	vdev->queue = q;
	INIT_LIST_HEAD(&vou_dev->buf_list);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_resume(&pdev->dev);

	i2c_adap = i2c_get_adapter(vou_pdata->i2c_adap);
	if (!i2c_adap) {
		ret = -ENODEV;
		goto ei2cgadap;
	}

	ret = sh_vou_hw_init(vou_dev);
	if (ret < 0)
		goto ereset;

	subdev = v4l2_i2c_new_subdev_board(&vou_dev->v4l2_dev, i2c_adap,
			vou_pdata->board_info, NULL);
	if (!subdev) {
		ret = -ENOMEM;
		goto ei2cnd;
	}

	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret < 0)
		goto evregdev;

	return 0;

evregdev:
ei2cnd:
ereset:
	i2c_put_adapter(i2c_adap);
ei2cgadap:
	pm_runtime_disable(&pdev->dev);
	v4l2_device_unregister(&vou_dev->v4l2_dev);
	return ret;
}