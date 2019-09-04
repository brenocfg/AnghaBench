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
struct spear_kbd {int /*<<< orphan*/  clk; int /*<<< orphan*/  input; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 struct spear_kbd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int spear_kbd_remove(struct platform_device *pdev)
{
	struct spear_kbd *kbd = platform_get_drvdata(pdev);

	input_unregister_device(kbd->input);
	clk_unprepare(kbd->clk);

	return 0;
}