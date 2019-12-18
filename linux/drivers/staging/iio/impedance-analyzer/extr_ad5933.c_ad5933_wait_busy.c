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
struct ad5933_state {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 unsigned char AD5933_MAX_RETRIES ; 
 int /*<<< orphan*/  AD5933_REG_STATUS ; 
 int EAGAIN ; 
 int ad5933_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int ad5933_wait_busy(struct ad5933_state *st, unsigned char event)
{
	unsigned char val, timeout = AD5933_MAX_RETRIES;
	int ret;

	while (timeout--) {
		ret =  ad5933_i2c_read(st->client, AD5933_REG_STATUS, 1, &val);
		if (ret < 0)
			return ret;
		if (val & event)
			return val;
		cpu_relax();
		mdelay(1);
	}

	return -EAGAIN;
}