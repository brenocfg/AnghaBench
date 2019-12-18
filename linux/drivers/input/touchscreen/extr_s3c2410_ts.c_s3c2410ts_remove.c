#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  io; int /*<<< orphan*/  input; int /*<<< orphan*/  clock; int /*<<< orphan*/  irq_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_timer ; 
 TYPE_1__ ts ; 

__attribute__((used)) static int s3c2410ts_remove(struct platform_device *pdev)
{
	free_irq(ts.irq_tc, ts.input);
	del_timer_sync(&touch_timer);

	clk_disable_unprepare(ts.clock);
	clk_put(ts.clock);

	input_unregister_device(ts.input);
	iounmap(ts.io);

	return 0;
}