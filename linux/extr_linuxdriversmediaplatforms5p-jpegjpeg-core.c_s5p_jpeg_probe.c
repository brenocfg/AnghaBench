#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct s5p_jpeg {int irq; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_dev; TYPE_1__* vfd_encoder; TYPE_1__* vfd_decoder; int /*<<< orphan*/  lock; TYPE_5__* variant; int /*<<< orphan*/ * clocks; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; int /*<<< orphan*/  slock; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int num_clocks; int /*<<< orphan*/  m2m_ops; int /*<<< orphan*/ * clk_names; int /*<<< orphan*/  jpeg_irq; } ;
struct TYPE_6__ {int minor; int /*<<< orphan*/  num; void* vfl_dir; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  (* release ) (TYPE_1__*) ;int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 char* S5P_JPEG_M2M_NAME ; 
 void* VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct s5p_jpeg* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_jpeg*) ; 
 TYPE_5__* jpeg_get_drv_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s5p_jpeg*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_jpeg_fops ; 
 int /*<<< orphan*/  s5p_jpeg_ioctl_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_set_max_seg_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_1__*) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct s5p_jpeg*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static int s5p_jpeg_probe(struct platform_device *pdev)
{
	struct s5p_jpeg *jpeg;
	struct resource *res;
	int i, ret;

	/* JPEG IP abstraction struct */
	jpeg = devm_kzalloc(&pdev->dev, sizeof(struct s5p_jpeg), GFP_KERNEL);
	if (!jpeg)
		return -ENOMEM;

	jpeg->variant = jpeg_get_drv_data(&pdev->dev);

	mutex_init(&jpeg->lock);
	spin_lock_init(&jpeg->slock);
	jpeg->dev = &pdev->dev;

	/* memory-mapped registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	jpeg->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(jpeg->regs))
		return PTR_ERR(jpeg->regs);

	/* interrupt service routine registration */
	jpeg->irq = ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot find IRQ\n");
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, jpeg->irq, jpeg->variant->jpeg_irq,
				0, dev_name(&pdev->dev), jpeg);
	if (ret) {
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", jpeg->irq);
		return ret;
	}

	/* clocks */
	for (i = 0; i < jpeg->variant->num_clocks; i++) {
		jpeg->clocks[i] = devm_clk_get(&pdev->dev,
					      jpeg->variant->clk_names[i]);
		if (IS_ERR(jpeg->clocks[i])) {
			dev_err(&pdev->dev, "failed to get clock: %s\n",
				jpeg->variant->clk_names[i]);
			return PTR_ERR(jpeg->clocks[i]);
		}
	}

	/* v4l2 device */
	ret = v4l2_device_register(&pdev->dev, &jpeg->v4l2_dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register v4l2 device\n");
		return ret;
	}

	/* mem2mem device */
	jpeg->m2m_dev = v4l2_m2m_init(jpeg->variant->m2m_ops);
	if (IS_ERR(jpeg->m2m_dev)) {
		v4l2_err(&jpeg->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(jpeg->m2m_dev);
		goto device_register_rollback;
	}

	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	/* JPEG encoder /dev/videoX node */
	jpeg->vfd_encoder = video_device_alloc();
	if (!jpeg->vfd_encoder) {
		v4l2_err(&jpeg->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		goto m2m_init_rollback;
	}
	snprintf(jpeg->vfd_encoder->name, sizeof(jpeg->vfd_encoder->name),
				"%s-enc", S5P_JPEG_M2M_NAME);
	jpeg->vfd_encoder->fops		= &s5p_jpeg_fops;
	jpeg->vfd_encoder->ioctl_ops	= &s5p_jpeg_ioctl_ops;
	jpeg->vfd_encoder->minor	= -1;
	jpeg->vfd_encoder->release	= video_device_release;
	jpeg->vfd_encoder->lock		= &jpeg->lock;
	jpeg->vfd_encoder->v4l2_dev	= &jpeg->v4l2_dev;
	jpeg->vfd_encoder->vfl_dir	= VFL_DIR_M2M;

	ret = video_register_device(jpeg->vfd_encoder, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(&jpeg->v4l2_dev, "Failed to register video device\n");
		video_device_release(jpeg->vfd_encoder);
		goto m2m_init_rollback;
	}

	video_set_drvdata(jpeg->vfd_encoder, jpeg);
	v4l2_info(&jpeg->v4l2_dev,
		  "encoder device registered as /dev/video%d\n",
		  jpeg->vfd_encoder->num);

	/* JPEG decoder /dev/videoX node */
	jpeg->vfd_decoder = video_device_alloc();
	if (!jpeg->vfd_decoder) {
		v4l2_err(&jpeg->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		goto enc_vdev_register_rollback;
	}
	snprintf(jpeg->vfd_decoder->name, sizeof(jpeg->vfd_decoder->name),
				"%s-dec", S5P_JPEG_M2M_NAME);
	jpeg->vfd_decoder->fops		= &s5p_jpeg_fops;
	jpeg->vfd_decoder->ioctl_ops	= &s5p_jpeg_ioctl_ops;
	jpeg->vfd_decoder->minor	= -1;
	jpeg->vfd_decoder->release	= video_device_release;
	jpeg->vfd_decoder->lock		= &jpeg->lock;
	jpeg->vfd_decoder->v4l2_dev	= &jpeg->v4l2_dev;
	jpeg->vfd_decoder->vfl_dir	= VFL_DIR_M2M;

	ret = video_register_device(jpeg->vfd_decoder, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(&jpeg->v4l2_dev, "Failed to register video device\n");
		video_device_release(jpeg->vfd_decoder);
		goto enc_vdev_register_rollback;
	}

	video_set_drvdata(jpeg->vfd_decoder, jpeg);
	v4l2_info(&jpeg->v4l2_dev,
		  "decoder device registered as /dev/video%d\n",
		  jpeg->vfd_decoder->num);

	/* final statements & power management */
	platform_set_drvdata(pdev, jpeg);

	pm_runtime_enable(&pdev->dev);

	v4l2_info(&jpeg->v4l2_dev, "Samsung S5P JPEG codec\n");

	return 0;

enc_vdev_register_rollback:
	video_unregister_device(jpeg->vfd_encoder);

m2m_init_rollback:
	v4l2_m2m_release(jpeg->m2m_dev);

device_register_rollback:
	v4l2_device_unregister(&jpeg->v4l2_dev);

	return ret;
}