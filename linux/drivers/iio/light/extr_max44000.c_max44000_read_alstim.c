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
struct max44000_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int MAX44000_CFG_RX_ALSTIM_MASK ; 
 unsigned int MAX44000_CFG_RX_ALSTIM_SHIFT ; 
 int /*<<< orphan*/  MAX44000_REG_CFG_RX ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max44000_read_alstim(struct max44000_data *data)
{
	unsigned int val;
	int ret;

	ret = regmap_read(data->regmap, MAX44000_REG_CFG_RX, &val);
	if (ret < 0)
		return ret;
	return (val & MAX44000_CFG_RX_ALSTIM_MASK) >> MAX44000_CFG_RX_ALSTIM_SHIFT;
}