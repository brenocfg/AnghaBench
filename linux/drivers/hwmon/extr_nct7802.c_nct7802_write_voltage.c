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
struct nct7802_data {int /*<<< orphan*/  access_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,int) ; 
 int /*<<< orphan*/ ** REG_VOLTAGE_LIMIT_LSB ; 
 int /*<<< orphan*/ * REG_VOLTAGE_LIMIT_MSB ; 
 int** REG_VOLTAGE_LIMIT_MSB_SHIFT ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* nct7802_vmul ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int nct7802_write_voltage(struct nct7802_data *data, int nr, int index,
				 unsigned long voltage)
{
	int shift = 8 - REG_VOLTAGE_LIMIT_MSB_SHIFT[index - 1][nr];
	int err;

	voltage = clamp_val(voltage, 0, 0x3ff * nct7802_vmul[nr]);
	voltage = DIV_ROUND_CLOSEST(voltage, nct7802_vmul[nr]);

	mutex_lock(&data->access_lock);
	err = regmap_write(data->regmap,
			   REG_VOLTAGE_LIMIT_LSB[index - 1][nr],
			   voltage & 0xff);
	if (err < 0)
		goto abort;

	err = regmap_update_bits(data->regmap, REG_VOLTAGE_LIMIT_MSB[nr],
				 0x0300 >> shift, (voltage & 0x0300) >> shift);
abort:
	mutex_unlock(&data->access_lock);
	return err;
}