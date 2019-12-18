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
typedef  struct smu10_power_state const smu10_power_state ;
struct pp_hw_power_state {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ SMU10_Magic ; 

__attribute__((used)) static const struct smu10_power_state *cast_const_smu10_ps(
				const struct pp_hw_power_state *hw_ps)
{
	if (SMU10_Magic != hw_ps->magic)
		return NULL;

	return (struct smu10_power_state *)hw_ps;
}