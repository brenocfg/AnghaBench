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
struct ad5360_state {TYPE_1__* vref_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 unsigned int ad5360_get_channel_vref_index (struct ad5360_state*,unsigned int) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5360_get_channel_vref(struct ad5360_state *st,
	unsigned int channel)
{
	unsigned int i = ad5360_get_channel_vref_index(st, channel);

	return regulator_get_voltage(st->vref_reg[i].consumer);
}