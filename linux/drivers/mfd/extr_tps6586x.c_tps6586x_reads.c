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
typedef  int /*<<< orphan*/  uint8_t ;
struct tps6586x {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tps6586x* dev_to_tps6586x (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

int tps6586x_reads(struct device *dev, int reg, int len, uint8_t *val)
{
	struct tps6586x *tps6586x = dev_to_tps6586x(dev);

	return regmap_bulk_read(tps6586x->regmap, reg, val, len);
}