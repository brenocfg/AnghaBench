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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fbd {int dummy; } ;
struct atmel_isi {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; int /*<<< orphan*/  fb_descriptors_phys; int /*<<< orphan*/  p_fb_descriptors; } ;

/* Variables and functions */
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_isi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_isi_remove(struct platform_device *pdev)
{
	struct atmel_isi *isi = platform_get_drvdata(pdev);

	dma_free_coherent(&pdev->dev,
			sizeof(struct fbd) * VIDEO_MAX_FRAME,
			isi->p_fb_descriptors,
			isi->fb_descriptors_phys);
	pm_runtime_disable(&pdev->dev);
	v4l2_async_notifier_unregister(&isi->notifier);
	v4l2_async_notifier_cleanup(&isi->notifier);
	v4l2_device_unregister(&isi->v4l2_dev);

	return 0;
}