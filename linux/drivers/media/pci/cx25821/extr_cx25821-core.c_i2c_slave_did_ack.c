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
struct i2c_adapter {struct cx25821_i2c* algo_data; } ;
struct cx25821_i2c {int /*<<< orphan*/  reg_stat; struct cx25821_dev* dev; } ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int cx_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int i2c_slave_did_ack(struct i2c_adapter *i2c_adap)
{
	struct cx25821_i2c *bus = i2c_adap->algo_data;
	struct cx25821_dev *dev = bus->dev;
	return cx_read(bus->reg_stat) & 0x01;
}