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
typedef  int /*<<< orphan*/  u8 ;
struct twl6040 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

int twl6040_reg_write(struct twl6040 *twl6040, unsigned int reg, u8 val)
{
	int ret;

	ret = regmap_write(twl6040->regmap, reg, val);

	return ret;
}