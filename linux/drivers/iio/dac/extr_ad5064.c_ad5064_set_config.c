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
struct ad5064_state {TYPE_1__* chip_info; } ;
struct TYPE_2__ {int regmap_type; } ;

/* Variables and functions */
 unsigned int AD5064_CMD_CONFIG ; 
 unsigned int AD5064_CMD_CONFIG_V2 ; 
#define  AD5064_REGMAP_ADI2 128 
 int ad5064_write (struct ad5064_state*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5064_set_config(struct ad5064_state *st, unsigned int val)
{
	unsigned int cmd;

	switch (st->chip_info->regmap_type) {
	case AD5064_REGMAP_ADI2:
		cmd = AD5064_CMD_CONFIG_V2;
		break;
	default:
		cmd = AD5064_CMD_CONFIG;
		break;
	}

	return ad5064_write(st, cmd, 0, val, 0);
}