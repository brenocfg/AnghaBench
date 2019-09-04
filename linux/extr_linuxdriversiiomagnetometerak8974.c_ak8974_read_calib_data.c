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
struct ak8974 {TYPE_1__* i2c; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_device_randomness (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,size_t) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void ak8974_read_calib_data(struct ak8974 *ak8974, unsigned int reg,
				   __le16 *tab, size_t tab_size)
{
	int ret = regmap_bulk_read(ak8974->map, reg, tab, tab_size);
	if (ret) {
		memset(tab, 0xFF, tab_size);
		dev_warn(&ak8974->i2c->dev,
			 "can't read calibration data (regs %u..%zu): %d\n",
			 reg, reg + tab_size - 1, ret);
	} else {
		add_device_randomness(tab, tab_size);
	}
}