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
struct ucb1400_ts {int /*<<< orphan*/  ts_idev; int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ucb1400_ts* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ucb1400_ts*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucb1400_ts_remove(struct platform_device *pdev)
{
	struct ucb1400_ts *ucb = dev_get_platdata(&pdev->dev);

	free_irq(ucb->irq, ucb);
	input_unregister_device(ucb->ts_idev);

	return 0;
}