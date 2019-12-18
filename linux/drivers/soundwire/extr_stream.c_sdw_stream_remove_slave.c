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
struct sdw_stream_runtime {int dummy; } ;
struct sdw_slave {TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdw_release_slave_stream (struct sdw_slave*,struct sdw_stream_runtime*) ; 
 int /*<<< orphan*/  sdw_slave_port_release (TYPE_1__*,struct sdw_slave*,struct sdw_stream_runtime*) ; 

int sdw_stream_remove_slave(struct sdw_slave *slave,
			    struct sdw_stream_runtime *stream)
{
	mutex_lock(&slave->bus->bus_lock);

	sdw_slave_port_release(slave->bus, slave, stream);
	sdw_release_slave_stream(slave, stream);

	mutex_unlock(&slave->bus->bus_lock);

	return 0;
}