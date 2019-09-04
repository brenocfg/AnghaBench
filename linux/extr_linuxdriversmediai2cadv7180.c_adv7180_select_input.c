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
struct adv7180_state {int dummy; } ;

/* Variables and functions */
 int ADV7180_INPUT_CONTROL_INSEL_MASK ; 
 int /*<<< orphan*/  ADV7180_REG_INPUT_CONTROL ; 
 int adv7180_read (struct adv7180_state*,int /*<<< orphan*/ ) ; 
 int adv7180_write (struct adv7180_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adv7180_select_input(struct adv7180_state *state, unsigned int input)
{
	int ret;

	ret = adv7180_read(state, ADV7180_REG_INPUT_CONTROL);
	if (ret < 0)
		return ret;

	ret &= ~ADV7180_INPUT_CONTROL_INSEL_MASK;
	ret |= input;
	return adv7180_write(state, ADV7180_REG_INPUT_CONTROL, ret);
}