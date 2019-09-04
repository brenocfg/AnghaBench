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
struct xiic_i2c {scalar_t__ tx_msg; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int xiic_bus_busy (struct xiic_i2c*) ; 

__attribute__((used)) static int xiic_busy(struct xiic_i2c *i2c)
{
	int tries = 3;
	int err;

	if (i2c->tx_msg)
		return -EBUSY;

	/* for instance if previous transfer was terminated due to TX error
	 * it might be that the bus is on it's way to become available
	 * give it at most 3 ms to wake
	 */
	err = xiic_bus_busy(i2c);
	while (err && tries--) {
		msleep(1);
		err = xiic_bus_busy(i2c);
	}

	return err;
}