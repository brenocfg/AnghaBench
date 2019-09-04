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
typedef  int u8 ;
struct pcf50633 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

u8 pcf50633_reg_read(struct pcf50633 *pcf, u8 reg)
{
	unsigned int val;
	int ret;

	ret = regmap_read(pcf->regmap, reg, &val);
	if (ret < 0)
		return -1;

	return val;
}