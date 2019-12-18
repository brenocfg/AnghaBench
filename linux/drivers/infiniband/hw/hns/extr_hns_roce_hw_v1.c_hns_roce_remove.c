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
struct platform_device {int dummy; } ;
struct hns_roce_dev {int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_exit (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hns_roce_remove(struct platform_device *pdev)
{
	struct hns_roce_dev *hr_dev = platform_get_drvdata(pdev);

	hns_roce_exit(hr_dev);
	kfree(hr_dev->priv);
	ib_dealloc_device(&hr_dev->ib_dev);

	return 0;
}