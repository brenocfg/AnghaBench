#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct cros_ec_device {int /*<<< orphan*/  event_notifier; } ;
struct TYPE_4__ {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ cbas_ec ; 
 int /*<<< orphan*/  cbas_ec_reglock ; 
 int /*<<< orphan*/  cbas_ec_set_input (int /*<<< orphan*/ *) ; 
 struct cros_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbas_ec_remove(struct platform_device *pdev)
{
	struct cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);

	mutex_lock(&cbas_ec_reglock);

	blocking_notifier_chain_unregister(&ec->event_notifier,
					   &cbas_ec.notifier);
	cbas_ec_set_input(NULL);

	mutex_unlock(&cbas_ec_reglock);
	return 0;
}