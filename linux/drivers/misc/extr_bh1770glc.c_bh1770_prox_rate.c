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
struct bh1770_chip {int prox_rate_threshold; int prox_rate; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_PS_MEAS_RATE ; 
 int PROX_ABOVE_THRESHOLD ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bh1770_prox_rate(struct bh1770_chip *chip, int mode)
{
	int rate;

	rate = (mode == PROX_ABOVE_THRESHOLD) ?
		chip->prox_rate_threshold : chip->prox_rate;

	return i2c_smbus_write_byte_data(chip->client,
					BH1770_PS_MEAS_RATE,
					rate);
}