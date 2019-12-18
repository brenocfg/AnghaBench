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
struct rproc {int has_iommu; struct keystone_rproc* priv; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct keystone_rproc {int irq_ring; int irq_fault; int kick_gpio; int /*<<< orphan*/  reset; struct device* dev; struct rproc* rproc; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 char* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keystone_rproc_dsp_reset (struct keystone_rproc*) ; 
 int keystone_rproc_of_get_dev_syscon (struct platform_device*,struct keystone_rproc*) ; 
 int keystone_rproc_of_get_memories (struct platform_device*,struct keystone_rproc*) ; 
 int /*<<< orphan*/  keystone_rproc_ops ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int of_get_named_gpio_flags (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ of_reserved_mem_device_init (struct device*) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct keystone_rproc*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int reset_control_status (int /*<<< orphan*/ ) ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int keystone_rproc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct keystone_rproc *ksproc;
	struct rproc *rproc;
	int dsp_id;
	char *fw_name = NULL;
	char *template = "keystone-dsp%d-fw";
	int name_len = 0;
	int ret = 0;

	if (!np) {
		dev_err(dev, "only DT-based devices are supported\n");
		return -ENODEV;
	}

	dsp_id = of_alias_get_id(np, "rproc");
	if (dsp_id < 0) {
		dev_warn(dev, "device does not have an alias id\n");
		return dsp_id;
	}

	/* construct a custom default fw name - subject to change in future */
	name_len = strlen(template); /* assuming a single digit alias */
	fw_name = devm_kzalloc(dev, name_len, GFP_KERNEL);
	if (!fw_name)
		return -ENOMEM;
	snprintf(fw_name, name_len, template, dsp_id);

	rproc = rproc_alloc(dev, dev_name(dev), &keystone_rproc_ops, fw_name,
			    sizeof(*ksproc));
	if (!rproc)
		return -ENOMEM;

	rproc->has_iommu = false;
	ksproc = rproc->priv;
	ksproc->rproc = rproc;
	ksproc->dev = dev;

	ret = keystone_rproc_of_get_dev_syscon(pdev, ksproc);
	if (ret)
		goto free_rproc;

	ksproc->reset = devm_reset_control_get_exclusive(dev, NULL);
	if (IS_ERR(ksproc->reset)) {
		ret = PTR_ERR(ksproc->reset);
		goto free_rproc;
	}

	/* enable clock for accessing DSP internal memories */
	pm_runtime_enable(dev);
	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		dev_err(dev, "failed to enable clock, status = %d\n", ret);
		pm_runtime_put_noidle(dev);
		goto disable_rpm;
	}

	ret = keystone_rproc_of_get_memories(pdev, ksproc);
	if (ret)
		goto disable_clk;

	ksproc->irq_ring = platform_get_irq_byname(pdev, "vring");
	if (ksproc->irq_ring < 0) {
		ret = ksproc->irq_ring;
		goto disable_clk;
	}

	ksproc->irq_fault = platform_get_irq_byname(pdev, "exception");
	if (ksproc->irq_fault < 0) {
		ret = ksproc->irq_fault;
		goto disable_clk;
	}

	ksproc->kick_gpio = of_get_named_gpio_flags(np, "kick-gpios", 0, NULL);
	if (ksproc->kick_gpio < 0) {
		ret = ksproc->kick_gpio;
		dev_err(dev, "failed to get gpio for virtio kicks, status = %d\n",
			ret);
		goto disable_clk;
	}

	if (of_reserved_mem_device_init(dev))
		dev_warn(dev, "device does not have specific CMA pool\n");

	/* ensure the DSP is in reset before loading firmware */
	ret = reset_control_status(ksproc->reset);
	if (ret < 0) {
		dev_err(dev, "failed to get reset status, status = %d\n", ret);
		goto release_mem;
	} else if (ret == 0) {
		WARN(1, "device is not in reset\n");
		keystone_rproc_dsp_reset(ksproc);
	}

	ret = rproc_add(rproc);
	if (ret) {
		dev_err(dev, "failed to add register device with remoteproc core, status = %d\n",
			ret);
		goto release_mem;
	}

	platform_set_drvdata(pdev, ksproc);

	return 0;

release_mem:
	of_reserved_mem_device_release(dev);
disable_clk:
	pm_runtime_put_sync(dev);
disable_rpm:
	pm_runtime_disable(dev);
free_rproc:
	rproc_free(rproc);
	return ret;
}