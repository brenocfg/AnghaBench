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
struct pcf2123_data {int /*<<< orphan*/  map; } ;
struct device {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (long,int) ; 
 int OFFSET_COARSE ; 
 int OFFSET_STEP ; 
 int /*<<< orphan*/  PCF2123_REG_OFFSET ; 
 struct pcf2123_data* dev_get_drvdata (struct device*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pcf2123_set_offset(struct device *dev, long offset)
{
	struct pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	s8 reg;

	if (offset > OFFSET_STEP * 127)
		reg = 127;
	else if (offset < OFFSET_STEP * -128)
		reg = -128;
	else
		reg = DIV_ROUND_CLOSEST(offset, OFFSET_STEP);

	/* choose fine offset only for odd values in the normal range */
	if (reg & 1 && reg <= 63 && reg >= -64) {
		/* Normal offset. Clear the coarse bit */
		reg &= ~OFFSET_COARSE;
	} else {
		/* Coarse offset. Divide by 2 and set the coarse bit */
		reg >>= 1;
		reg |= OFFSET_COARSE;
	}

	return regmap_write(pcf2123->map, PCF2123_REG_OFFSET, (unsigned int)reg);
}