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
struct bmc150_magn_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_MAGN_REG_X_L ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int bmc150_magn_reset_intr(struct bmc150_magn_data *data)
{
	int tmp;

	/*
	 * Data Ready (DRDY) is always cleared after
	 * readout of data registers ends.
	 */
	return regmap_read(data->regmap, BMC150_MAGN_REG_X_L, &tmp);
}