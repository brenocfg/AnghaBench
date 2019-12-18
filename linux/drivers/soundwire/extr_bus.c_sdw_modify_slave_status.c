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
struct sdw_slave {int status; TYPE_1__* bus; } ;
typedef  enum sdw_slave_status { ____Placeholder_sdw_slave_status } sdw_slave_status ;
struct TYPE_2__ {int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdw_modify_slave_status(struct sdw_slave *slave,
				    enum sdw_slave_status status)
{
	mutex_lock(&slave->bus->bus_lock);
	slave->status = status;
	mutex_unlock(&slave->bus->bus_lock);
}