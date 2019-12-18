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
struct adp5061_state {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5061_TERM_SET ; 
 int /*<<< orphan*/  ADP5061_TERM_SET_CHG_VLIM_MODE (int) ; 
 int /*<<< orphan*/  ADP5061_TERM_SET_CHG_VLIM_MSK ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp5061_const_chg_vmax ; 
 int adp5061_get_array_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adp5061_set_const_chg_vmax(struct adp5061_state *st, int val)
{
	int index;

	/* Convert from uV to mV */
	val /= 1000;
	index = adp5061_get_array_index(adp5061_const_chg_vmax,
					ARRAY_SIZE(adp5061_const_chg_vmax),
					val);
	if (index < 0)
		return index;

	return regmap_update_bits(st->regmap, ADP5061_TERM_SET,
				  ADP5061_TERM_SET_CHG_VLIM_MSK,
				  ADP5061_TERM_SET_CHG_VLIM_MODE(index));
}