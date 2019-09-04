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
struct w90p910_ts {int /*<<< orphan*/  input; int /*<<< orphan*/  clk; int /*<<< orphan*/  ts_reg; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq_num; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct w90p910_ts*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct w90p910_ts*) ; 
 struct w90p910_ts* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int w90x900ts_remove(struct platform_device *pdev)
{
	struct w90p910_ts *w90p910_ts = platform_get_drvdata(pdev);
	struct resource *res;

	free_irq(w90p910_ts->irq_num, w90p910_ts);
	del_timer_sync(&w90p910_ts->timer);
	iounmap(w90p910_ts->ts_reg);

	clk_put(w90p910_ts->clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	input_unregister_device(w90p910_ts->input);
	kfree(w90p910_ts);

	return 0;
}