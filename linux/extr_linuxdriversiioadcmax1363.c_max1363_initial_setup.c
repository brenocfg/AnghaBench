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
struct max1363_state {int setupbyte; int /*<<< orphan*/  configbyte; TYPE_1__* chip_info; int /*<<< orphan*/ * current_mode; scalar_t__ vref; } ;
struct TYPE_2__ {size_t default_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX1363_CONFIG_BYTE (int /*<<< orphan*/ ) ; 
 int MAX1363_SETUP_AIN3_IS_AIN3_REF_IS_INT ; 
 int MAX1363_SETUP_AIN3_IS_REF_EXT_TO_REF ; 
 int MAX1363_SETUP_BYTE (int) ; 
 int MAX1363_SETUP_INT_CLOCK ; 
 int MAX1363_SETUP_NORESET ; 
 int MAX1363_SETUP_POWER_UP_INT_REF ; 
 int MAX1363_SETUP_UNIPOLAR ; 
 int /*<<< orphan*/ * max1363_mode_table ; 
 int max1363_set_scan_mode (struct max1363_state*) ; 

__attribute__((used)) static int max1363_initial_setup(struct max1363_state *st)
{
	st->setupbyte = MAX1363_SETUP_INT_CLOCK
		| MAX1363_SETUP_UNIPOLAR
		| MAX1363_SETUP_NORESET;

	if (st->vref)
		st->setupbyte |= MAX1363_SETUP_AIN3_IS_REF_EXT_TO_REF;
	else
		st->setupbyte |= MAX1363_SETUP_POWER_UP_INT_REF
		  | MAX1363_SETUP_AIN3_IS_AIN3_REF_IS_INT;

	/* Set scan mode writes the config anyway so wait until then */
	st->setupbyte = MAX1363_SETUP_BYTE(st->setupbyte);
	st->current_mode = &max1363_mode_table[st->chip_info->default_mode];
	st->configbyte = MAX1363_CONFIG_BYTE(st->configbyte);

	return max1363_set_scan_mode(st);
}