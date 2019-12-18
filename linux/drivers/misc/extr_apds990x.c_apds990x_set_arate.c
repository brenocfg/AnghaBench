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
struct apds990x_chip {int lux_persistence; int arate; int prox_persistence; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int APDS990X_APERS_SHIFT ; 
 int /*<<< orphan*/  APDS990X_PERS ; 
 int APDS990X_PPERS_SHIFT ; 
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int apds990x_write_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int) ; 
 int* apersis ; 
 int* arates_hz ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds990x_set_arate(struct apds990x_chip *chip, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(arates_hz); i++)
		if (rate >= arates_hz[i])
			break;

	if (i == ARRAY_SIZE(arates_hz))
		return -EINVAL;

	/* Pick up corresponding persistence value */
	chip->lux_persistence = apersis[i];
	chip->arate = arates_hz[i];

	/* If the chip is not in use, don't try to access it */
	if (pm_runtime_suspended(&chip->client->dev))
		return 0;

	/* Persistence levels */
	return apds990x_write_byte(chip, APDS990X_PERS,
			(chip->lux_persistence << APDS990X_APERS_SHIFT) |
			(chip->prox_persistence << APDS990X_PPERS_SHIFT));
}