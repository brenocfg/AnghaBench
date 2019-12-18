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
struct saa7164_unit {scalar_t__ type; scalar_t__ i2c_bus_nr; int i2c_bus_addr; int i2c_reg_len; } ;
struct saa7164_i2c {scalar_t__ nr; struct saa7164_dev* dev; } ;
struct saa7164_dev {size_t board; } ;
struct TYPE_2__ {struct saa7164_unit* unit; } ;

/* Variables and functions */
 int SAA7164_MAX_UNITS ; 
 scalar_t__ SAA7164_UNIT_UNDEFINED ; 
 TYPE_1__* saa7164_boards ; 

int saa7164_i2caddr_to_reglen(struct saa7164_i2c *bus, int addr)
{
	/* For a given bus and i2c device address, return the
	 * saa7164 registry address width. < 0 on error
	 */

	struct saa7164_dev *dev = bus->dev;
	struct saa7164_unit *unit;
	int i;

	for (i = 0; i < SAA7164_MAX_UNITS; i++) {
		unit = &saa7164_boards[dev->board].unit[i];

		if (unit->type == SAA7164_UNIT_UNDEFINED)
			continue;

		if ((bus->nr == unit->i2c_bus_nr) &&
			(addr == unit->i2c_bus_addr))
			return unit->i2c_reg_len;
	}

	return -1;
}