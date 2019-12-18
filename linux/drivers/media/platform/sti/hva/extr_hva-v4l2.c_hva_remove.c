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
struct platform_device {int /*<<< orphan*/  name; } ;
struct hva_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  work_queue; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVA_PREFIX ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hva_debugfs_remove (struct hva_dev*) ; 
 int /*<<< orphan*/  hva_hw_remove (struct hva_dev*) ; 
 struct device* hva_to_dev (struct hva_dev*) ; 
 int /*<<< orphan*/  hva_unregister_device (struct hva_dev*) ; 
 struct hva_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hva_remove(struct platform_device *pdev)
{
	struct hva_dev *hva = platform_get_drvdata(pdev);
	struct device *dev = hva_to_dev(hva);

	hva_unregister_device(hva);

	destroy_workqueue(hva->work_queue);

	hva_hw_remove(hva);

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_remove(hva);
#endif

	v4l2_device_unregister(&hva->v4l2_dev);

	dev_info(dev, "%s %s removed\n", HVA_PREFIX, pdev->name);

	return 0;
}