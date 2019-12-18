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
struct TYPE_2__ {scalar_t__ input; } ;

/* Variables and functions */
 int EBUSY ; 
 int __cbas_ec_probe (struct platform_device*) ; 
 TYPE_1__ cbas_ec ; 
 int /*<<< orphan*/  cbas_ec_reglock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbas_ec_probe(struct platform_device *pdev)
{
	int retval;

	mutex_lock(&cbas_ec_reglock);

	if (cbas_ec.input) {
		retval = -EBUSY;
		goto out;
	}

	retval = __cbas_ec_probe(pdev);

out:
	mutex_unlock(&cbas_ec_reglock);
	return retval;
}