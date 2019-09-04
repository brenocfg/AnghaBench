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
struct adv7180_state {int /*<<< orphan*/  vpp_client; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int adv7180_vpp_write(struct adv7180_state *state, unsigned int reg,
	unsigned int value)
{
	return i2c_smbus_write_byte_data(state->vpp_client, reg, value);
}