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
 int /*<<< orphan*/  ADP5061_TERM_SET_VTRM_MODE (int) ; 
 int /*<<< orphan*/  ADP5061_TERM_SET_VTRM_MSK ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int adp5061_get_array_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adp5061_vmax ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adp5061_set_max_voltage(struct adp5061_state *st, int val)
{
	int vmax_index;

	/* Convert from uV to mV */
	val /= 1000;
	if (val > 4500)
		val = 4500;

	vmax_index = adp5061_get_array_index(adp5061_vmax,
					     ARRAY_SIZE(adp5061_vmax), val);
	if (vmax_index < 0)
		return vmax_index;

	vmax_index += 0x0F;

	return regmap_update_bits(st->regmap, ADP5061_TERM_SET,
				  ADP5061_TERM_SET_VTRM_MSK,
				  ADP5061_TERM_SET_VTRM_MODE(vmax_index));
}