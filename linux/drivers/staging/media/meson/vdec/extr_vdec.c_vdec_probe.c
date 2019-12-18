#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct video_device {int device_caps; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  (* release ) (struct video_device*) ;int /*<<< orphan*/  name; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct amvdec_core {int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; struct device* dev_dec; struct video_device* vdev_dec; int /*<<< orphan*/  platform; struct device* dev; void* vdec_hevc_clk; void* vdec_1_clk; void* dos_clk; void* dos_parser_clk; void* canvas; void* regmap_ao; void* esparser_base; void* dos_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct amvdec_core* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct amvdec_core*) ; 
 int esparser_init (struct platform_device*,struct amvdec_core*) ; 
 void* meson_canvas_get (struct device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct amvdec_core*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 void* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int v4l2_device_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdec_dt_match ; 
 int /*<<< orphan*/  vdec_fops ; 
 int /*<<< orphan*/  vdec_ioctl_ops ; 
 int /*<<< orphan*/  vdec_isr ; 
 int /*<<< orphan*/  vdec_threaded_isr ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct amvdec_core*) ; 

__attribute__((used)) static int vdec_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct video_device *vdev;
	struct amvdec_core *core;
	struct resource *r;
	const struct of_device_id *of_id;
	int irq;
	int ret;

	core = devm_kzalloc(dev, sizeof(*core), GFP_KERNEL);
	if (!core)
		return -ENOMEM;

	core->dev = dev;
	platform_set_drvdata(pdev, core);

	r = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dos");
	core->dos_base = devm_ioremap_resource(dev, r);
	if (IS_ERR(core->dos_base)) {
		dev_err(dev, "Couldn't remap DOS memory\n");
		return PTR_ERR(core->dos_base);
	}

	r = platform_get_resource_byname(pdev, IORESOURCE_MEM, "esparser");
	core->esparser_base = devm_ioremap_resource(dev, r);
	if (IS_ERR(core->esparser_base)) {
		dev_err(dev, "Couldn't remap ESPARSER memory\n");
		return PTR_ERR(core->esparser_base);
	}

	core->regmap_ao =
		syscon_regmap_lookup_by_phandle(dev->of_node,
						"amlogic,ao-sysctrl");
	if (IS_ERR(core->regmap_ao)) {
		dev_err(dev, "Couldn't regmap AO sysctrl\n");
		return PTR_ERR(core->regmap_ao);
	}

	core->canvas = meson_canvas_get(dev);
	if (IS_ERR(core->canvas))
		return PTR_ERR(core->canvas);

	core->dos_parser_clk = devm_clk_get(dev, "dos_parser");
	if (IS_ERR(core->dos_parser_clk))
		return -EPROBE_DEFER;

	core->dos_clk = devm_clk_get(dev, "dos");
	if (IS_ERR(core->dos_clk))
		return -EPROBE_DEFER;

	core->vdec_1_clk = devm_clk_get(dev, "vdec_1");
	if (IS_ERR(core->vdec_1_clk))
		return -EPROBE_DEFER;

	core->vdec_hevc_clk = devm_clk_get(dev, "vdec_hevc");
	if (IS_ERR(core->vdec_hevc_clk))
		return -EPROBE_DEFER;

	irq = platform_get_irq_byname(pdev, "vdec");
	if (irq < 0)
		return irq;

	ret = devm_request_threaded_irq(core->dev, irq, vdec_isr,
					vdec_threaded_isr, IRQF_ONESHOT,
					"vdec", core);
	if (ret)
		return ret;

	ret = esparser_init(pdev, core);
	if (ret)
		return ret;

	ret = v4l2_device_register(dev, &core->v4l2_dev);
	if (ret) {
		dev_err(dev, "Couldn't register v4l2 device\n");
		return -ENOMEM;
	}

	vdev = video_device_alloc();
	if (!vdev) {
		ret = -ENOMEM;
		goto err_vdev_release;
	}

	of_id = of_match_node(vdec_dt_match, dev->of_node);
	core->platform = of_id->data;
	core->vdev_dec = vdev;
	core->dev_dec = dev;
	mutex_init(&core->lock);

	strscpy(vdev->name, "meson-video-decoder", sizeof(vdev->name));
	vdev->release = video_device_release;
	vdev->fops = &vdec_fops;
	vdev->ioctl_ops = &vdec_ioctl_ops;
	vdev->vfl_dir = VFL_DIR_M2M;
	vdev->v4l2_dev = &core->v4l2_dev;
	vdev->lock = &core->lock;
	vdev->device_caps = V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING;

	video_set_drvdata(vdev, core);

	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		dev_err(dev, "Failed registering video device\n");
		goto err_vdev_release;
	}

	return 0;

err_vdev_release:
	video_device_release(vdev);
	return ret;
}