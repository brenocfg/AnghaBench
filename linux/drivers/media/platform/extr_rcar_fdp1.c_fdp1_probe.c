#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct video_device {int /*<<< orphan*/  num; int /*<<< orphan*/  name; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; } ;
struct resource {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct fdp1_dev {int irq; int /*<<< orphan*/  v4l2_dev; struct clk* m2m_dev; TYPE_1__* dev; int /*<<< orphan*/  dev_mutex; struct video_device vfd; int /*<<< orphan*/  clk_rate; struct clk* fcp; struct clk* regs; int /*<<< orphan*/  device_process_lock; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  free_job_list; TYPE_12__* jobs; int /*<<< orphan*/  hw_job_list; int /*<<< orphan*/  queued_job_list; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_12__*) ; 
 int ENOMEM ; 
#define  FD1_IP_E3 132 
#define  FD1_IP_H3 131 
#define  FD1_IP_H3_ES1 130 
 int /*<<< orphan*/  FD1_IP_INTDATA ; 
#define  FD1_IP_M3N 129 
#define  FD1_IP_M3W 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 struct clk* clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct clk* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct fdp1_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fdp1_dev*) ; 
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*) ; 
 int /*<<< orphan*/  fdp1_irq_handler ; 
 int fdp1_read (struct fdp1_dev*,int /*<<< orphan*/ ) ; 
 struct video_device fdp1_videodev ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m2m_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fdp1_dev*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_1__*) ; 
 struct clk* rcar_fcp_get (struct device_node*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_device_register (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct clk* v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (struct clk*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct fdp1_dev*) ; 

__attribute__((used)) static int fdp1_probe(struct platform_device *pdev)
{
	struct fdp1_dev *fdp1;
	struct video_device *vfd;
	struct device_node *fcp_node;
	struct resource *res;
	struct clk *clk;
	unsigned int i;

	int ret;
	int hw_version;

	fdp1 = devm_kzalloc(&pdev->dev, sizeof(*fdp1), GFP_KERNEL);
	if (!fdp1)
		return -ENOMEM;

	INIT_LIST_HEAD(&fdp1->free_job_list);
	INIT_LIST_HEAD(&fdp1->queued_job_list);
	INIT_LIST_HEAD(&fdp1->hw_job_list);

	/* Initialise the jobs on the free list */
	for (i = 0; i < ARRAY_SIZE(fdp1->jobs); i++)
		list_add(&fdp1->jobs[i].list, &fdp1->free_job_list);

	mutex_init(&fdp1->dev_mutex);

	spin_lock_init(&fdp1->irqlock);
	spin_lock_init(&fdp1->device_process_lock);
	fdp1->dev = &pdev->dev;
	platform_set_drvdata(pdev, fdp1);

	/* Memory-mapped registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	fdp1->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(fdp1->regs))
		return PTR_ERR(fdp1->regs);

	/* Interrupt service routine registration */
	fdp1->irq = ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot find IRQ\n");
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, fdp1->irq, fdp1_irq_handler, 0,
			       dev_name(&pdev->dev), fdp1);
	if (ret) {
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", fdp1->irq);
		return ret;
	}

	/* FCP */
	fcp_node = of_parse_phandle(pdev->dev.of_node, "renesas,fcp", 0);
	if (fcp_node) {
		fdp1->fcp = rcar_fcp_get(fcp_node);
		of_node_put(fcp_node);
		if (IS_ERR(fdp1->fcp)) {
			dev_dbg(&pdev->dev, "FCP not found (%ld)\n",
				PTR_ERR(fdp1->fcp));
			return PTR_ERR(fdp1->fcp);
		}
	}

	/* Determine our clock rate */
	clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	fdp1->clk_rate = clk_get_rate(clk);
	clk_put(clk);

	/* V4L2 device registration */
	ret = v4l2_device_register(&pdev->dev, &fdp1->v4l2_dev);
	if (ret) {
		v4l2_err(&fdp1->v4l2_dev, "Failed to register video device\n");
		return ret;
	}

	/* M2M registration */
	fdp1->m2m_dev = v4l2_m2m_init(&m2m_ops);
	if (IS_ERR(fdp1->m2m_dev)) {
		v4l2_err(&fdp1->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(fdp1->m2m_dev);
		goto unreg_dev;
	}

	/* Video registration */
	fdp1->vfd = fdp1_videodev;
	vfd = &fdp1->vfd;
	vfd->lock = &fdp1->dev_mutex;
	vfd->v4l2_dev = &fdp1->v4l2_dev;
	video_set_drvdata(vfd, fdp1);
	strscpy(vfd->name, fdp1_videodev.name, sizeof(vfd->name));

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, 0);
	if (ret) {
		v4l2_err(&fdp1->v4l2_dev, "Failed to register video device\n");
		goto release_m2m;
	}

	v4l2_info(&fdp1->v4l2_dev, "Device registered as /dev/video%d\n",
		  vfd->num);

	/* Power up the cells to read HW */
	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(fdp1->dev);

	hw_version = fdp1_read(fdp1, FD1_IP_INTDATA);
	switch (hw_version) {
	case FD1_IP_H3_ES1:
		dprintk(fdp1, "FDP1 Version R-Car H3 ES1\n");
		break;
	case FD1_IP_M3W:
		dprintk(fdp1, "FDP1 Version R-Car M3-W\n");
		break;
	case FD1_IP_H3:
		dprintk(fdp1, "FDP1 Version R-Car H3\n");
		break;
	case FD1_IP_M3N:
		dprintk(fdp1, "FDP1 Version R-Car M3N\n");
		break;
	case FD1_IP_E3:
		dprintk(fdp1, "FDP1 Version R-Car E3\n");
		break;
	default:
		dev_err(fdp1->dev, "FDP1 Unidentifiable (0x%08x)\n",
			hw_version);
	}

	/* Allow the hw to sleep until an open call puts it to use */
	pm_runtime_put(fdp1->dev);

	return 0;

release_m2m:
	v4l2_m2m_release(fdp1->m2m_dev);

unreg_dev:
	v4l2_device_unregister(&fdp1->v4l2_dev);

	return ret;
}