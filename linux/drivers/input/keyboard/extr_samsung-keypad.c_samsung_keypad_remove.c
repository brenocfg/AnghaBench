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
struct samsung_keypad {int /*<<< orphan*/  clk; int /*<<< orphan*/  input_dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 struct samsung_keypad* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int samsung_keypad_remove(struct platform_device *pdev)
{
	struct samsung_keypad *keypad = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);

	input_unregister_device(keypad->input_dev);

	clk_unprepare(keypad->clk);

	return 0;
}