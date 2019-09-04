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
struct adv7180_state {int /*<<< orphan*/  client; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv7180_select_page (struct adv7180_state*,unsigned int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv7180_read(struct adv7180_state *state, unsigned int reg)
{
	lockdep_assert_held(&state->mutex);
	adv7180_select_page(state, reg >> 8);
	return i2c_smbus_read_byte_data(state->client, reg & 0xff);
}