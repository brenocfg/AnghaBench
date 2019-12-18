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
struct opp_table {int /*<<< orphan*/  lock; } ;
struct opp_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct opp_device* _add_opp_dev_unlocked (struct device const*,struct opp_table*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct opp_device *_add_opp_dev(const struct device *dev,
				struct opp_table *opp_table)
{
	struct opp_device *opp_dev;

	mutex_lock(&opp_table->lock);
	opp_dev = _add_opp_dev_unlocked(dev, opp_table);
	mutex_unlock(&opp_table->lock);

	return opp_dev;
}