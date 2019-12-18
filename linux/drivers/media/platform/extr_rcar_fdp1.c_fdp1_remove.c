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
struct fdp1_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vfd; int /*<<< orphan*/  m2m_dev; } ;

/* Variables and functions */
 struct fdp1_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fdp1_remove(struct platform_device *pdev)
{
	struct fdp1_dev *fdp1 = platform_get_drvdata(pdev);

	v4l2_m2m_release(fdp1->m2m_dev);
	video_unregister_device(&fdp1->vfd);
	v4l2_device_unregister(&fdp1->v4l2_dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}