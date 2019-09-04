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
struct i2c_msg {scalar_t__ addr; } ;
struct cx231xx_i2c {int /*<<< orphan*/  nr; } ;
struct TYPE_2__ {int tuner_i2c_master; scalar_t__ tuner_addr; } ;
struct cx231xx {int tuner_type; TYPE_1__ board; } ;

/* Variables and functions */
 int get_real_i2c_port (struct cx231xx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_tuner(struct cx231xx *dev, struct cx231xx_i2c *bus,
			const struct i2c_msg *msg, int tuner_type)
{
	int i2c_port = get_real_i2c_port(dev, bus->nr);

	if (i2c_port != dev->board.tuner_i2c_master)
		return false;

	if (msg->addr != dev->board.tuner_addr)
		return false;

	if (dev->tuner_type != tuner_type)
		return false;

	return true;
}