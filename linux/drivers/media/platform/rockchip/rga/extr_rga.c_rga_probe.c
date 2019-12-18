#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct video_device {int name; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; } ;
struct TYPE_16__ {int major; int minor; } ;
struct rockchip_rga {unsigned int* src_mmu_pages; unsigned int* dst_mmu_pages; TYPE_3__* dev; int /*<<< orphan*/  v4l2_dev; struct video_device* vfd; int /*<<< orphan*/  cmdbuf_phy; int /*<<< orphan*/  cmdbuf_virt; TYPE_1__ version; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regs; int /*<<< orphan*/  ctrl_lock; } ;
struct resource {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_17__ {int depth; } ;
struct TYPE_15__ {int stride; int width; int size; int height; TYPE_2__* fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGA_CMDBUF_SIZE ; 
 int /*<<< orphan*/  RGA_VERSION_INFO ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int) ; 
 TYPE_14__ def_frame ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct rockchip_rga* devm_kzalloc (TYPE_3__*,int,int) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rockchip_rga*) ; 
 int /*<<< orphan*/  dma_alloc_attrs (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rockchip_rga*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_3__*) ; 
 int /*<<< orphan*/  rga_isr ; 
 int /*<<< orphan*/  rga_m2m_ops ; 
 int rga_parse_dt (struct rockchip_rga*) ; 
 int rga_read (struct rockchip_rga*,int /*<<< orphan*/ ) ; 
 struct video_device rga_videodev ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 struct video_device* video_device_alloc () ; 
 int video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct rockchip_rga*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static int rga_probe(struct platform_device *pdev)
{
	struct rockchip_rga *rga;
	struct video_device *vfd;
	struct resource *res;
	int ret = 0;
	int irq;

	if (!pdev->dev.of_node)
		return -ENODEV;

	rga = devm_kzalloc(&pdev->dev, sizeof(*rga), GFP_KERNEL);
	if (!rga)
		return -ENOMEM;

	rga->dev = &pdev->dev;
	spin_lock_init(&rga->ctrl_lock);
	mutex_init(&rga->mutex);

	ret = rga_parse_dt(rga);
	if (ret)
		dev_err(&pdev->dev, "Unable to parse OF data\n");

	pm_runtime_enable(rga->dev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	rga->regs = devm_ioremap_resource(rga->dev, res);
	if (IS_ERR(rga->regs)) {
		ret = PTR_ERR(rga->regs);
		goto err_put_clk;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto err_put_clk;
	}

	ret = devm_request_irq(rga->dev, irq, rga_isr, 0,
			       dev_name(rga->dev), rga);
	if (ret < 0) {
		dev_err(rga->dev, "failed to request irq\n");
		goto err_put_clk;
	}

	ret = v4l2_device_register(&pdev->dev, &rga->v4l2_dev);
	if (ret)
		goto err_put_clk;
	vfd = video_device_alloc();
	if (!vfd) {
		v4l2_err(&rga->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		goto unreg_v4l2_dev;
	}
	*vfd = rga_videodev;
	vfd->lock = &rga->mutex;
	vfd->v4l2_dev = &rga->v4l2_dev;

	video_set_drvdata(vfd, rga);
	rga->vfd = vfd;

	platform_set_drvdata(pdev, rga);
	rga->m2m_dev = v4l2_m2m_init(&rga_m2m_ops);
	if (IS_ERR(rga->m2m_dev)) {
		v4l2_err(&rga->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(rga->m2m_dev);
		goto unreg_video_dev;
	}

	pm_runtime_get_sync(rga->dev);

	rga->version.major = (rga_read(rga, RGA_VERSION_INFO) >> 24) & 0xFF;
	rga->version.minor = (rga_read(rga, RGA_VERSION_INFO) >> 20) & 0x0F;

	v4l2_info(&rga->v4l2_dev, "HW Version: 0x%02x.%02x\n",
		  rga->version.major, rga->version.minor);

	pm_runtime_put(rga->dev);

	/* Create CMD buffer */
	rga->cmdbuf_virt = dma_alloc_attrs(rga->dev, RGA_CMDBUF_SIZE,
					   &rga->cmdbuf_phy, GFP_KERNEL,
					   DMA_ATTR_WRITE_COMBINE);

	rga->src_mmu_pages =
		(unsigned int *)__get_free_pages(GFP_KERNEL | __GFP_ZERO, 3);
	rga->dst_mmu_pages =
		(unsigned int *)__get_free_pages(GFP_KERNEL | __GFP_ZERO, 3);

	def_frame.stride = (def_frame.width * def_frame.fmt->depth) >> 3;
	def_frame.size = def_frame.stride * def_frame.height;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(&rga->v4l2_dev, "Failed to register video device\n");
		goto rel_vdev;
	}

	v4l2_info(&rga->v4l2_dev, "Registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));

	return 0;

rel_vdev:
	video_device_release(vfd);
unreg_video_dev:
	video_unregister_device(rga->vfd);
unreg_v4l2_dev:
	v4l2_device_unregister(&rga->v4l2_dev);
err_put_clk:
	pm_runtime_disable(rga->dev);

	return ret;
}