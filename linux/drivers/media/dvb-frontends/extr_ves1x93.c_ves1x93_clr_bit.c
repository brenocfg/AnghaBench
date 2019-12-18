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
struct ves1x93_state {int* init_1x93_tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ves1x93_writereg (struct ves1x93_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ves1x93_clr_bit (struct ves1x93_state* state)
{
	msleep(10);
	ves1x93_writereg (state, 0, state->init_1x93_tab[0] & 0xfe);
	ves1x93_writereg (state, 0, state->init_1x93_tab[0]);
	msleep(50);
	return 0;
}