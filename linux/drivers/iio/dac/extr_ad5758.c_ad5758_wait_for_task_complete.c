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
struct ad5758_state {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ad5758_spi_reg_read (struct ad5758_state*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad5758_wait_for_task_complete(struct ad5758_state *st,
					 unsigned int reg,
					 unsigned int mask)
{
	unsigned int timeout;
	int ret;

	timeout = 10;
	do {
		ret = ad5758_spi_reg_read(st, reg);
		if (ret < 0)
			return ret;

		if (!(ret & mask))
			return 0;

		usleep_range(100, 1000);
	} while (--timeout);

	dev_err(&st->spi->dev,
		"Error reading bit 0x%x in 0x%x register\n", mask, reg);

	return -EIO;
}