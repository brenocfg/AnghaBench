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
struct w90p910_keypad {int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct w90p910_keypad*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct w90p910_keypad*) ; 
 struct w90p910_keypad* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int w90p910_keypad_remove(struct platform_device *pdev)
{
	struct w90p910_keypad *keypad = platform_get_drvdata(pdev);
	struct resource *res;

	free_irq(keypad->irq, keypad);

	clk_put(keypad->clk);

	input_unregister_device(keypad->input_dev);

	iounmap(keypad->mmio_base);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	kfree(keypad);

	return 0;
}