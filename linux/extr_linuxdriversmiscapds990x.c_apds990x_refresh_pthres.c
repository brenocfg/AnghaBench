#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct apds990x_chip {int prox_thres; scalar_t__ prox_continuous_mode; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_PIHTL ; 
 int /*<<< orphan*/  APDS990X_PILTL ; 
 int APDS_PROX_HYSTERESIS ; 
 int APDS_RANGE ; 
 int apds990x_write_word (struct apds990x_chip*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds990x_refresh_pthres(struct apds990x_chip *chip, int data)
{
	int ret, lo, hi;

	/* If the chip is not in use, don't try to access it */
	if (pm_runtime_suspended(&chip->client->dev))
		return 0;

	if (data < chip->prox_thres) {
		lo = 0;
		hi = chip->prox_thres;
	} else {
		lo = chip->prox_thres - APDS_PROX_HYSTERESIS;
		if (chip->prox_continuous_mode)
			hi = chip->prox_thres;
		else
			hi = APDS_RANGE;
	}

	ret = apds990x_write_word(chip, APDS990X_PILTL, lo);
	ret |= apds990x_write_word(chip, APDS990X_PIHTL, hi);
	return ret;
}