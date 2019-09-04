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
struct apds990x_chip {int lux_persistence; int prox_persistence; int again_meas; int again_next; int pdrive; int pdiode; int pgain; TYPE_1__* pdata; } ;
struct TYPE_2__ {int ppcount; } ;

/* Variables and functions */
 int APDS990X_APERS_SHIFT ; 
 int /*<<< orphan*/  APDS990X_CONFIG ; 
 int /*<<< orphan*/  APDS990X_CONTROL ; 
 int /*<<< orphan*/  APDS990X_ENABLE ; 
 int APDS990X_EN_DISABLE_ALL ; 
 int /*<<< orphan*/  APDS990X_PERS ; 
 int /*<<< orphan*/  APDS990X_PPCOUNT ; 
 int APDS990X_PPERS_SHIFT ; 
 int /*<<< orphan*/  APDS990X_PTIME ; 
 int APDS990X_PTIME_DEFAULT ; 
 int /*<<< orphan*/  APDS990X_WTIME ; 
 int APDS990X_WTIME_DEFAULT ; 
 int /*<<< orphan*/  APDS_LUX_AVERAGING_TIME ; 
 int /*<<< orphan*/  apds990x_set_atime (struct apds990x_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apds990x_write_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int apds990x_configure(struct apds990x_chip *chip)
{
	/* It is recommended to use disabled mode during these operations */
	apds990x_write_byte(chip, APDS990X_ENABLE, APDS990X_EN_DISABLE_ALL);

	/* conversion and wait times for different state machince states */
	apds990x_write_byte(chip, APDS990X_PTIME, APDS990X_PTIME_DEFAULT);
	apds990x_write_byte(chip, APDS990X_WTIME, APDS990X_WTIME_DEFAULT);
	apds990x_set_atime(chip, APDS_LUX_AVERAGING_TIME);

	apds990x_write_byte(chip, APDS990X_CONFIG, 0);

	/* Persistence levels */
	apds990x_write_byte(chip, APDS990X_PERS,
			(chip->lux_persistence << APDS990X_APERS_SHIFT) |
			(chip->prox_persistence << APDS990X_PPERS_SHIFT));

	apds990x_write_byte(chip, APDS990X_PPCOUNT, chip->pdata->ppcount);

	/* Start with relatively small gain */
	chip->again_meas = 1;
	chip->again_next = 1;
	apds990x_write_byte(chip, APDS990X_CONTROL,
			(chip->pdrive << 6) |
			(chip->pdiode << 4) |
			(chip->pgain << 2) |
			(chip->again_next << 0));
	return 0;
}