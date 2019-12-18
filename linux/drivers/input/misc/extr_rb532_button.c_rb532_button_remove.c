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
struct input_polled_dev {int dummy; } ;

/* Variables and functions */
 struct input_polled_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_free_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_unregister_polled_device (struct input_polled_dev*) ; 

__attribute__((used)) static int rb532_button_remove(struct platform_device *pdev)
{
	struct input_polled_dev *poll_dev = dev_get_drvdata(&pdev->dev);

	input_unregister_polled_device(poll_dev);
	input_free_polled_device(poll_dev);

	return 0;
}