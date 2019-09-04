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
struct pm80x_onkey_info {int /*<<< orphan*/  idev; int /*<<< orphan*/  irq; int /*<<< orphan*/  pm80x; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pm80x_onkey_info*) ; 
 struct pm80x_onkey_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm80x_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pm80x_onkey_info*) ; 

__attribute__((used)) static int pm80x_onkey_remove(struct platform_device *pdev)
{
	struct pm80x_onkey_info *info = platform_get_drvdata(pdev);

	pm80x_free_irq(info->pm80x, info->irq, info);
	input_unregister_device(info->idev);
	kfree(info);
	return 0;
}