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
struct ucb1400 {int /*<<< orphan*/  ucb1400_gpio; int /*<<< orphan*/  ucb1400_ts; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ucb1400* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ucb1400*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucb1400_core_remove(struct device *dev)
{
	struct ucb1400 *ucb = dev_get_drvdata(dev);

	platform_device_unregister(ucb->ucb1400_ts);
	platform_device_unregister(ucb->ucb1400_gpio);

	kfree(ucb);
	return 0;
}