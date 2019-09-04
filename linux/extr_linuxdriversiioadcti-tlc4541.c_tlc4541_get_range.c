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
struct tlc4541_state {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tlc4541_get_range(struct tlc4541_state *st)
{
	int vref;

	vref = regulator_get_voltage(st->reg);
	if (vref < 0)
		return vref;

	vref /= 1000;

	return vref;
}