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
struct buttons_dev {int /*<<< orphan*/  poll_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buttons_dev*) ; 
 struct buttons_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sgi_buttons_remove(struct platform_device *pdev)
{
	struct buttons_dev *bdev = platform_get_drvdata(pdev);

	input_unregister_polled_device(bdev->poll_dev);
	input_free_polled_device(bdev->poll_dev);
	kfree(bdev);

	return 0;
}