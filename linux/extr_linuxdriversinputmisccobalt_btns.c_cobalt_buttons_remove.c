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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct buttons_dev {int /*<<< orphan*/  reg; int /*<<< orphan*/  poll_dev; } ;

/* Variables and functions */
 struct buttons_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buttons_dev*) ; 

__attribute__((used)) static int cobalt_buttons_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct buttons_dev *bdev = dev_get_drvdata(dev);

	input_unregister_polled_device(bdev->poll_dev);
	input_free_polled_device(bdev->poll_dev);
	iounmap(bdev->reg);
	kfree(bdev);

	return 0;
}