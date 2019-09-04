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
struct sdw_slave {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sdw_slave* dev_to_sdw_dev (struct device*) ; 
 int sdw_read (struct sdw_slave*,unsigned int) ; 

__attribute__((used)) static int regmap_sdw_read(void *context, unsigned int reg, unsigned int *val)
{
	struct device *dev = context;
	struct sdw_slave *slave = dev_to_sdw_dev(dev);
	int read;

	read = sdw_read(slave, reg);
	if (read < 0)
		return read;

	*val = read;
	return 0;
}