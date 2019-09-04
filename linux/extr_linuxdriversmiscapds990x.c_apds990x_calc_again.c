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
struct apds990x_chip {int again_meas; int lux_clear; int a_max_result; int again_next; int pdrive; int pdiode; int pgain; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_CONTROL ; 
 int APDS990X_MAX_AGAIN ; 
 int APDS_LUX_GAIN_LO_LIMIT ; 
 int APDS_LUX_GAIN_LO_LIMIT_STRICT ; 
 int ERANGE ; 
 int /*<<< orphan*/  apds990x_force_a_refresh (struct apds990x_chip*) ; 
 int /*<<< orphan*/  apds990x_refresh_athres (struct apds990x_chip*) ; 
 int /*<<< orphan*/  apds990x_write_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int apds990x_calc_again(struct apds990x_chip *chip)
{
	int curr_again = chip->again_meas;
	int next_again = chip->again_meas;
	int ret = 0;

	/* Calculate suitable als gain */
	if (chip->lux_clear == chip->a_max_result)
		next_again -= 2; /* ALS saturated. Decrease gain by 2 steps */
	else if (chip->lux_clear > chip->a_max_result / 2)
		next_again--;
	else if (chip->lux_clear < APDS_LUX_GAIN_LO_LIMIT_STRICT)
		next_again += 2; /* Too dark. Increase gain by 2 steps */
	else if (chip->lux_clear < APDS_LUX_GAIN_LO_LIMIT)
		next_again++;

	/* Limit gain to available range */
	if (next_again < 0)
		next_again = 0;
	else if (next_again > APDS990X_MAX_AGAIN)
		next_again = APDS990X_MAX_AGAIN;

	/* Let's check can we trust the measured result */
	if (chip->lux_clear == chip->a_max_result)
		/* Result can be totally garbage due to saturation */
		ret = -ERANGE;
	else if (next_again != curr_again &&
		chip->lux_clear < APDS_LUX_GAIN_LO_LIMIT_STRICT)
		/*
		 * Gain is changed and measurement result is very small.
		 * Result can be totally garbage due to underflow
		 */
		ret = -ERANGE;

	chip->again_next = next_again;
	apds990x_write_byte(chip, APDS990X_CONTROL,
			(chip->pdrive << 6) |
			(chip->pdiode << 4) |
			(chip->pgain << 2) |
			(chip->again_next << 0));

	/*
	 * Error means bad result -> re-measurement is needed. The forced
	 * refresh uses fastest possible persistence setting to get result
	 * as soon as possible.
	 */
	if (ret < 0)
		apds990x_force_a_refresh(chip);
	else
		apds990x_refresh_athres(chip);

	return ret;
}