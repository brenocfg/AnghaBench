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
struct resource {int dummy; } ;
struct panfrost_device {int /*<<< orphan*/  iomem; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  as_lock; int /*<<< orphan*/  as_lru_list; int /*<<< orphan*/  scheduled_jobs; int /*<<< orphan*/  reset_lock; int /*<<< orphan*/  sched_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panfrost_clk_fini (struct panfrost_device*) ; 
 int panfrost_clk_init (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_gpu_fini (struct panfrost_device*) ; 
 int panfrost_gpu_init (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_job_fini (struct panfrost_device*) ; 
 int panfrost_job_init (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_mmu_fini (struct panfrost_device*) ; 
 int panfrost_mmu_init (struct panfrost_device*) ; 
 int panfrost_perfcnt_init (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_regulator_fini (struct panfrost_device*) ; 
 int panfrost_regulator_init (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_reset_fini (struct panfrost_device*) ; 
 int panfrost_reset_init (struct panfrost_device*) ; 
 struct resource* platform_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int panfrost_device_init(struct panfrost_device *pfdev)
{
	int err;
	struct resource *res;

	mutex_init(&pfdev->sched_lock);
	mutex_init(&pfdev->reset_lock);
	INIT_LIST_HEAD(&pfdev->scheduled_jobs);
	INIT_LIST_HEAD(&pfdev->as_lru_list);

	spin_lock_init(&pfdev->as_lock);

	err = panfrost_clk_init(pfdev);
	if (err) {
		dev_err(pfdev->dev, "clk init failed %d\n", err);
		return err;
	}

	err = panfrost_regulator_init(pfdev);
	if (err) {
		dev_err(pfdev->dev, "regulator init failed %d\n", err);
		goto err_out0;
	}

	err = panfrost_reset_init(pfdev);
	if (err) {
		dev_err(pfdev->dev, "reset init failed %d\n", err);
		goto err_out1;
	}

	res = platform_get_resource(pfdev->pdev, IORESOURCE_MEM, 0);
	pfdev->iomem = devm_ioremap_resource(pfdev->dev, res);
	if (IS_ERR(pfdev->iomem)) {
		dev_err(pfdev->dev, "failed to ioremap iomem\n");
		err = PTR_ERR(pfdev->iomem);
		goto err_out2;
	}

	err = panfrost_gpu_init(pfdev);
	if (err)
		goto err_out2;

	err = panfrost_mmu_init(pfdev);
	if (err)
		goto err_out3;

	err = panfrost_job_init(pfdev);
	if (err)
		goto err_out4;

	err = panfrost_perfcnt_init(pfdev);
	if (err)
		goto err_out5;

	return 0;
err_out5:
	panfrost_job_fini(pfdev);
err_out4:
	panfrost_mmu_fini(pfdev);
err_out3:
	panfrost_gpu_fini(pfdev);
err_out2:
	panfrost_reset_fini(pfdev);
err_out1:
	panfrost_regulator_fini(pfdev);
err_out0:
	panfrost_clk_fini(pfdev);
	return err;
}