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
struct TYPE_2__ {int demod_chip; } ;
struct lgdt330x_state {TYPE_1__ config; } ;

/* Variables and functions */
 int ENODEV ; 
#define  LGDT3302 129 
#define  LGDT3303 128 
 int lgdt3302_sw_reset (struct lgdt330x_state*) ; 
 int lgdt3303_sw_reset (struct lgdt330x_state*) ; 

__attribute__((used)) static int lgdt330x_sw_reset(struct lgdt330x_state *state)
{
	switch (state->config.demod_chip) {
	case LGDT3302:
		return lgdt3302_sw_reset(state);
	case LGDT3303:
		return lgdt3303_sw_reset(state);
	default:
		return -ENODEV;
	}
}