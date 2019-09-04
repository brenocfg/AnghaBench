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
struct tps65218 {int /*<<< orphan*/  tps_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int tps65218_reg_write (struct tps65218*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int tps65218_update_bits(struct tps65218 *tps, unsigned int reg,
		unsigned int mask, unsigned int val, unsigned int level)
{
	int ret;
	unsigned int data;

	ret = regmap_read(tps->regmap, reg, &data);
	if (ret) {
		dev_err(tps->dev, "Read from reg 0x%x failed\n", reg);
		return ret;
	}

	data &= ~mask;
	data |= val & mask;

	mutex_lock(&tps->tps_lock);
	ret = tps65218_reg_write(tps, reg, data, level);
	if (ret)
		dev_err(tps->dev, "Write for reg 0x%x failed\n", reg);
	mutex_unlock(&tps->tps_lock);

	return ret;
}