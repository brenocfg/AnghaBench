#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int minor; int /*<<< orphan*/  num; void* vfl_dir; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; void* release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; } ;
struct jpu {int irq; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_dev; TYPE_1__ vfd_encoder; TYPE_1__ vfd_decoder; int /*<<< orphan*/  mutex; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned int JPU_MAX_QUALITY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct jpu* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jpu*) ; 
 scalar_t__* jpeg_hdrs ; 
 int /*<<< orphan*/  jpu_fops ; 
 int /*<<< orphan*/  jpu_generate_hdr (unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  jpu_ioctl_ops ; 
 int /*<<< orphan*/  jpu_irq_handler ; 
 int /*<<< orphan*/  jpu_m2m_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jpu*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 void* video_device_release_empty ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct jpu*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static int jpu_probe(struct platform_device *pdev)
{
	struct jpu *jpu;
	struct resource *res;
	int ret;
	unsigned int i;

	jpu = devm_kzalloc(&pdev->dev, sizeof(*jpu), GFP_KERNEL);
	if (!jpu)
		return -ENOMEM;

	mutex_init(&jpu->mutex);
	spin_lock_init(&jpu->lock);
	jpu->dev = &pdev->dev;

	/* memory-mapped registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	jpu->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(jpu->regs))
		return PTR_ERR(jpu->regs);

	/* interrupt service routine registration */
	jpu->irq = ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot find IRQ\n");
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, jpu->irq, jpu_irq_handler, 0,
			       dev_name(&pdev->dev), jpu);
	if (ret) {
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", jpu->irq);
		return ret;
	}

	/* clocks */
	jpu->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(jpu->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return PTR_ERR(jpu->clk);
	}

	/* v4l2 device */
	ret = v4l2_device_register(&pdev->dev, &jpu->v4l2_dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register v4l2 device\n");
		return ret;
	}

	/* mem2mem device */
	jpu->m2m_dev = v4l2_m2m_init(&jpu_m2m_ops);
	if (IS_ERR(jpu->m2m_dev)) {
		v4l2_err(&jpu->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(jpu->m2m_dev);
		goto device_register_rollback;
	}

	/* fill in qantization and Huffman tables for encoder */
	for (i = 0; i < JPU_MAX_QUALITY; i++)
		jpu_generate_hdr(i, (unsigned char *)jpeg_hdrs[i]);

	strlcpy(jpu->vfd_encoder.name, DRV_NAME, sizeof(jpu->vfd_encoder.name));
	jpu->vfd_encoder.fops		= &jpu_fops;
	jpu->vfd_encoder.ioctl_ops	= &jpu_ioctl_ops;
	jpu->vfd_encoder.minor		= -1;
	jpu->vfd_encoder.release	= video_device_release_empty;
	jpu->vfd_encoder.lock		= &jpu->mutex;
	jpu->vfd_encoder.v4l2_dev	= &jpu->v4l2_dev;
	jpu->vfd_encoder.vfl_dir	= VFL_DIR_M2M;

	ret = video_register_device(&jpu->vfd_encoder, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(&jpu->v4l2_dev, "Failed to register video device\n");
		goto m2m_init_rollback;
	}

	video_set_drvdata(&jpu->vfd_encoder, jpu);

	strlcpy(jpu->vfd_decoder.name, DRV_NAME, sizeof(jpu->vfd_decoder.name));
	jpu->vfd_decoder.fops		= &jpu_fops;
	jpu->vfd_decoder.ioctl_ops	= &jpu_ioctl_ops;
	jpu->vfd_decoder.minor		= -1;
	jpu->vfd_decoder.release	= video_device_release_empty;
	jpu->vfd_decoder.lock		= &jpu->mutex;
	jpu->vfd_decoder.v4l2_dev	= &jpu->v4l2_dev;
	jpu->vfd_decoder.vfl_dir	= VFL_DIR_M2M;

	ret = video_register_device(&jpu->vfd_decoder, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(&jpu->v4l2_dev, "Failed to register video device\n");
		goto enc_vdev_register_rollback;
	}

	video_set_drvdata(&jpu->vfd_decoder, jpu);
	platform_set_drvdata(pdev, jpu);

	v4l2_info(&jpu->v4l2_dev, "encoder device registered as /dev/video%d\n",
		  jpu->vfd_encoder.num);
	v4l2_info(&jpu->v4l2_dev, "decoder device registered as /dev/video%d\n",
		  jpu->vfd_decoder.num);

	return 0;

enc_vdev_register_rollback:
	video_unregister_device(&jpu->vfd_encoder);

m2m_init_rollback:
	v4l2_m2m_release(jpu->m2m_dev);

device_register_rollback:
	v4l2_device_unregister(&jpu->v4l2_dev);

	return ret;
}