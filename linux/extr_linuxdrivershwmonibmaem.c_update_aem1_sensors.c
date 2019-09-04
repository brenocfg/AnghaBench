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
struct aem_data {int /*<<< orphan*/  lock; scalar_t__ valid; scalar_t__ last_updated; } ;

/* Variables and functions */
 scalar_t__ REFRESH_INTERVAL ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  update_aem_energy (struct aem_data*) ; 

__attribute__((used)) static void update_aem1_sensors(struct aem_data *data)
{
	mutex_lock(&data->lock);
	if (time_before(jiffies, data->last_updated + REFRESH_INTERVAL) &&
	    data->valid)
		goto out;

	update_aem_energy(data);
out:
	mutex_unlock(&data->lock);
}