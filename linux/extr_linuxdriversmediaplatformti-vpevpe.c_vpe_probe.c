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
struct vpe_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/ * vpdma; int /*<<< orphan*/  vpdma_data; int /*<<< orphan*/  csc; int /*<<< orphan*/  sc; int /*<<< orphan*/  base; TYPE_1__* res; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  num_instances; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_32K ; 
 int /*<<< orphan*/  VPE_MODULE_NAME ; 
 int /*<<< orphan*/  VPE_PID ; 
 int /*<<< orphan*/  VPE_PID_FUNC_MASK ; 
 int /*<<< orphan*/  VPE_PID_FUNC_SHIFT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csc_create (struct platform_device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vpe_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vpe_dev*) ; 
 int /*<<< orphan*/  m2m_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vpe_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int read_field_reg (struct vpe_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_create (struct platform_device*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int vpdma_create (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_dbg (struct vpe_dev*,char*,int) ; 
 int /*<<< orphan*/  vpe_err (struct vpe_dev*,char*) ; 
 int /*<<< orphan*/  vpe_fw_cb ; 
 int /*<<< orphan*/  vpe_irq ; 
 int vpe_runtime_get (struct platform_device*) ; 
 int /*<<< orphan*/  vpe_runtime_put (struct platform_device*) ; 
 int /*<<< orphan*/  vpe_set_clock_enable (struct vpe_dev*,int) ; 
 int /*<<< orphan*/  vpe_top_reset (struct vpe_dev*) ; 
 int /*<<< orphan*/  vpe_top_vpdma_reset (struct vpe_dev*) ; 

__attribute__((used)) static int vpe_probe(struct platform_device *pdev)
{
	struct vpe_dev *dev;
	int ret, irq, func;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	spin_lock_init(&dev->lock);

	ret = v4l2_device_register(&pdev->dev, &dev->v4l2_dev);
	if (ret)
		return ret;

	atomic_set(&dev->num_instances, 0);
	mutex_init(&dev->dev_mutex);

	dev->res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
			"vpe_top");
	/*
	 * HACK: we get resource info from device tree in the form of a list of
	 * VPE sub blocks, the driver currently uses only the base of vpe_top
	 * for register access, the driver should be changed later to access
	 * registers based on the sub block base addresses
	 */
	dev->base = devm_ioremap(&pdev->dev, dev->res->start, SZ_32K);
	if (!dev->base) {
		ret = -ENOMEM;
		goto v4l2_dev_unreg;
	}

	irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq, vpe_irq, 0, VPE_MODULE_NAME,
			dev);
	if (ret)
		goto v4l2_dev_unreg;

	platform_set_drvdata(pdev, dev);

	dev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	if (IS_ERR(dev->m2m_dev)) {
		vpe_err(dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(dev->m2m_dev);
		goto v4l2_dev_unreg;
	}

	pm_runtime_enable(&pdev->dev);

	ret = vpe_runtime_get(pdev);
	if (ret)
		goto rel_m2m;

	/* Perform clk enable followed by reset */
	vpe_set_clock_enable(dev, 1);

	vpe_top_reset(dev);

	func = read_field_reg(dev, VPE_PID, VPE_PID_FUNC_MASK,
		VPE_PID_FUNC_SHIFT);
	vpe_dbg(dev, "VPE PID function %x\n", func);

	vpe_top_vpdma_reset(dev);

	dev->sc = sc_create(pdev, "sc");
	if (IS_ERR(dev->sc)) {
		ret = PTR_ERR(dev->sc);
		goto runtime_put;
	}

	dev->csc = csc_create(pdev, "csc");
	if (IS_ERR(dev->csc)) {
		ret = PTR_ERR(dev->csc);
		goto runtime_put;
	}

	dev->vpdma = &dev->vpdma_data;
	ret = vpdma_create(pdev, dev->vpdma, vpe_fw_cb);
	if (ret)
		goto runtime_put;

	return 0;

runtime_put:
	vpe_runtime_put(pdev);
rel_m2m:
	pm_runtime_disable(&pdev->dev);
	v4l2_m2m_release(dev->m2m_dev);
v4l2_dev_unreg:
	v4l2_device_unregister(&dev->v4l2_dev);

	return ret;
}