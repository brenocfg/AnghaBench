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
struct smu8_power_state {int dummy; } ;
struct pp_hw_power_state {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ smu8_magic ; 

__attribute__((used)) static struct smu8_power_state *cast_smu8_power_state(struct pp_hw_power_state *hw_ps)
{
	if (smu8_magic != hw_ps->magic)
		return NULL;

	return (struct smu8_power_state *)hw_ps;
}