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
struct ts_nbus {int /*<<< orphan*/  lock; int /*<<< orphan*/  pwm; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ts_nbus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts_nbus_remove(struct platform_device *pdev)
{
	struct ts_nbus *ts_nbus = dev_get_drvdata(&pdev->dev);

	/* shutdown the FPGA */
	mutex_lock(&ts_nbus->lock);
	pwm_disable(ts_nbus->pwm);
	mutex_unlock(&ts_nbus->lock);

	return 0;
}