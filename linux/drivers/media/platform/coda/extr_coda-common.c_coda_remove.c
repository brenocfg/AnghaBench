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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ vaddr; } ;
struct coda_dev {int /*<<< orphan*/  ida; int /*<<< orphan*/  debugfs_root; int /*<<< orphan*/  workbuf; int /*<<< orphan*/  tempbuf; int /*<<< orphan*/  codebuf; TYPE_1__ iram; int /*<<< orphan*/  iram_pool; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  v4l2_dev; scalar_t__ m2m_dev; int /*<<< orphan*/ * vfd; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coda_free_aux_buf (struct coda_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 struct coda_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (scalar_t__) ; 
 scalar_t__ video_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coda_remove(struct platform_device *pdev)
{
	struct coda_dev *dev = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < ARRAY_SIZE(dev->vfd); i++) {
		if (video_get_drvdata(&dev->vfd[i]))
			video_unregister_device(&dev->vfd[i]);
	}
	if (dev->m2m_dev)
		v4l2_m2m_release(dev->m2m_dev);
	pm_runtime_disable(&pdev->dev);
	v4l2_device_unregister(&dev->v4l2_dev);
	destroy_workqueue(dev->workqueue);
	if (dev->iram.vaddr)
		gen_pool_free(dev->iram_pool, (unsigned long)dev->iram.vaddr,
			      dev->iram.size);
	coda_free_aux_buf(dev, &dev->codebuf);
	coda_free_aux_buf(dev, &dev->tempbuf);
	coda_free_aux_buf(dev, &dev->workbuf);
	debugfs_remove_recursive(dev->debugfs_root);
	ida_destroy(&dev->ida);
	return 0;
}