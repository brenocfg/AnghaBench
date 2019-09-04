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
struct apds990x_chip {int /*<<< orphan*/  lux_thres_hi; int /*<<< orphan*/  lux_thres_lo; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_AIHTL ; 
 int /*<<< orphan*/  APDS990X_AILTL ; 
 int /*<<< orphan*/  apds990x_lux_to_threshold (struct apds990x_chip*,int /*<<< orphan*/ ) ; 
 int apds990x_write_word (struct apds990x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds990x_refresh_athres(struct apds990x_chip *chip)
{
	int ret;
	/* If the chip is not in use, don't try to access it */
	if (pm_runtime_suspended(&chip->client->dev))
		return 0;

	ret = apds990x_write_word(chip, APDS990X_AILTL,
			apds990x_lux_to_threshold(chip, chip->lux_thres_lo));
	ret |= apds990x_write_word(chip, APDS990X_AIHTL,
			apds990x_lux_to_threshold(chip, chip->lux_thres_hi));

	return ret;
}