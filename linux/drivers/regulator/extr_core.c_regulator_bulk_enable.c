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
struct regulator_bulk_data {int ret; int /*<<< orphan*/  consumer; int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_DOMAIN_EXCLUSIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_domain ; 
 int /*<<< orphan*/  async_schedule_domain (int /*<<< orphan*/ ,struct regulator_bulk_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_synchronize_full_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_enable_async ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

int regulator_bulk_enable(int num_consumers,
			  struct regulator_bulk_data *consumers)
{
	ASYNC_DOMAIN_EXCLUSIVE(async_domain);
	int i;
	int ret = 0;

	for (i = 0; i < num_consumers; i++) {
		async_schedule_domain(regulator_bulk_enable_async,
				      &consumers[i], &async_domain);
	}

	async_synchronize_full_domain(&async_domain);

	/* If any consumer failed we need to unwind any that succeeded */
	for (i = 0; i < num_consumers; i++) {
		if (consumers[i].ret != 0) {
			ret = consumers[i].ret;
			goto err;
		}
	}

	return 0;

err:
	for (i = 0; i < num_consumers; i++) {
		if (consumers[i].ret < 0)
			pr_err("Failed to enable %s: %d\n", consumers[i].supply,
			       consumers[i].ret);
		else
			regulator_disable(consumers[i].consumer);
	}

	return ret;
}