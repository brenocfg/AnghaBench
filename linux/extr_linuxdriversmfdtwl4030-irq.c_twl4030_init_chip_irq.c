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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_sih_modules ; 
 int /*<<< orphan*/  sih_modules ; 
 int /*<<< orphan*/  sih_modules_twl4030 ; 
 int /*<<< orphan*/  sih_modules_twl5031 ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int twl4030_init_chip_irq(const char *chip)
{
	if (!strcmp(chip, "twl5031")) {
		sih_modules = sih_modules_twl5031;
		nr_sih_modules = ARRAY_SIZE(sih_modules_twl5031);
	} else {
		sih_modules = sih_modules_twl4030;
		nr_sih_modules = ARRAY_SIZE(sih_modules_twl4030);
	}

	return 0;
}