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
struct ad7298_state {int /*<<< orphan*/  reg; scalar_t__ ext_ref; } ;

/* Variables and functions */
 int AD7298_INTREF_mV ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7298_get_ref_voltage(struct ad7298_state *st)
{
	int vref;

	if (st->ext_ref) {
		vref = regulator_get_voltage(st->reg);
		if (vref < 0)
			return vref;

		return vref / 1000;
	} else {
		return AD7298_INTREF_mV;
	}
}