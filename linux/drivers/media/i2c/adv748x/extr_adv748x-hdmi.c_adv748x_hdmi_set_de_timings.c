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
typedef  int u8 ;
struct adv748x_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CP_DE_POS_END_LOW ; 
 int /*<<< orphan*/  ADV748X_CP_DE_POS_HIGH ; 
 int ADV748X_CP_DE_POS_HIGH_SET ; 
 int /*<<< orphan*/  ADV748X_CP_DE_POS_START_LOW ; 
 int /*<<< orphan*/  cp_write (struct adv748x_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adv748x_hdmi_set_de_timings(struct adv748x_state *state, int shift)
{
	u8 high, low;

	/* POS_HIGH stores bits 8 and 9 of both the start and end */
	high = ADV748X_CP_DE_POS_HIGH_SET;
	high |= (shift & 0x300) >> 8;
	low = shift & 0xff;

	/* The sequence of the writes is important and must be followed */
	cp_write(state, ADV748X_CP_DE_POS_HIGH, high);
	cp_write(state, ADV748X_CP_DE_POS_END_LOW, low);

	high |= (shift & 0x300) >> 6;

	cp_write(state, ADV748X_CP_DE_POS_HIGH, high);
	cp_write(state, ADV748X_CP_DE_POS_START_LOW, low);
}