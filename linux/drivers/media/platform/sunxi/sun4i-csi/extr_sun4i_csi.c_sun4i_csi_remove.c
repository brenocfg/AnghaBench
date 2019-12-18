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
struct sun4i_csi {int /*<<< orphan*/  mdev; int /*<<< orphan*/  notifier; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 struct sun4i_csi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sun4i_csi_dma_unregister (struct sun4i_csi*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun4i_csi_remove(struct platform_device *pdev)
{
	struct sun4i_csi *csi = platform_get_drvdata(pdev);

	v4l2_async_notifier_unregister(&csi->notifier);
	v4l2_async_notifier_cleanup(&csi->notifier);
	media_device_unregister(&csi->mdev);
	sun4i_csi_dma_unregister(csi);
	media_device_cleanup(&csi->mdev);

	return 0;
}