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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct goldfish_pipe_dev {scalar_t__ version; scalar_t__ base; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/ * magic; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PIPE_CURRENT_DEVICE_VERSION ; 
 int /*<<< orphan*/  PIPE_DRIVER_VERSION ; 
 scalar_t__ PIPE_REG_VERSION ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct goldfish_pipe_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goldfish_pipe_device_deinit ; 
 int goldfish_pipe_device_init (struct platform_device*,struct goldfish_pipe_dev*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int goldfish_pipe_probe(struct platform_device *pdev)
{
	struct resource *r;
	struct goldfish_pipe_dev *dev;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->magic = &goldfish_pipe_device_deinit;
	spin_lock_init(&dev->lock);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r || resource_size(r) < PAGE_SIZE) {
		dev_err(&pdev->dev, "can't allocate i/o page\n");
		return -EINVAL;
	}
	dev->base = devm_ioremap(&pdev->dev, r->start, PAGE_SIZE);
	if (!dev->base) {
		dev_err(&pdev->dev, "ioremap failed\n");
		return -EINVAL;
	}

	r = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!r)
		return -EINVAL;

	dev->irq = r->start;

	/*
	 * Exchange the versions with the host device
	 *
	 * Note: v1 driver used to not report its version, so we write it before
	 *  reading device version back: this allows the host implementation to
	 *  detect the old driver (if there was no version write before read).
	 */
	writel(PIPE_DRIVER_VERSION, dev->base + PIPE_REG_VERSION);
	dev->version = readl(dev->base + PIPE_REG_VERSION);
	if (WARN_ON(dev->version < PIPE_CURRENT_DEVICE_VERSION))
		return -EINVAL;

	return goldfish_pipe_device_init(pdev, dev);
}