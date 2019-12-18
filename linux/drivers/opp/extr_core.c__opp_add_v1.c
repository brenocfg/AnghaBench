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
struct opp_table {long voltage_tolerance_v1; int /*<<< orphan*/  head; } ;
struct device {int dummy; } ;
struct dev_pm_opp {unsigned long rate; int available; int dynamic; TYPE_1__* supplies; } ;
struct TYPE_2__ {long u_volt; long u_volt_min; long u_volt_max; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OPP_EVENT_ADD ; 
 int _opp_add (struct device*,struct dev_pm_opp*,struct opp_table*,int) ; 
 struct dev_pm_opp* _opp_allocate (struct opp_table*) ; 
 int /*<<< orphan*/  _opp_free (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dev_pm_opp*) ; 

int _opp_add_v1(struct opp_table *opp_table, struct device *dev,
		unsigned long freq, long u_volt, bool dynamic)
{
	struct dev_pm_opp *new_opp;
	unsigned long tol;
	int ret;

	new_opp = _opp_allocate(opp_table);
	if (!new_opp)
		return -ENOMEM;

	/* populate the opp table */
	new_opp->rate = freq;
	tol = u_volt * opp_table->voltage_tolerance_v1 / 100;
	new_opp->supplies[0].u_volt = u_volt;
	new_opp->supplies[0].u_volt_min = u_volt - tol;
	new_opp->supplies[0].u_volt_max = u_volt + tol;
	new_opp->available = true;
	new_opp->dynamic = dynamic;

	ret = _opp_add(dev, new_opp, opp_table, false);
	if (ret) {
		/* Don't return error for duplicate OPPs */
		if (ret == -EBUSY)
			ret = 0;
		goto free_opp;
	}

	/*
	 * Notify the changes in the availability of the operable
	 * frequency/voltage list.
	 */
	blocking_notifier_call_chain(&opp_table->head, OPP_EVENT_ADD, new_opp);
	return 0;

free_opp:
	_opp_free(new_opp);

	return ret;
}