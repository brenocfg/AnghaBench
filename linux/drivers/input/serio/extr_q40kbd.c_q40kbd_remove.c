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
struct q40kbd {int /*<<< orphan*/  port; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q40_IRQ_KEYBOARD ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct q40kbd*) ; 
 int /*<<< orphan*/  kfree (struct q40kbd*) ; 
 struct q40kbd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q40kbd_remove(struct platform_device *pdev)
{
	struct q40kbd *q40kbd = platform_get_drvdata(pdev);

	/*
	 * q40kbd_close() will be called as part of unregistering
	 * and will ensure that IRQ is turned off, so it is safe
	 * to unregister port first and free IRQ later.
	 */
	serio_unregister_port(q40kbd->port);
	free_irq(Q40_IRQ_KEYBOARD, q40kbd);
	kfree(q40kbd);

	return 0;
}