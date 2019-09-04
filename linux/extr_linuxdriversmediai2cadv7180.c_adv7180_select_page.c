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
struct adv7180_state {unsigned int register_page; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7180_REG_CTRL ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adv7180_select_page(struct adv7180_state *state, unsigned int page)
{
	if (state->register_page != page) {
		i2c_smbus_write_byte_data(state->client, ADV7180_REG_CTRL,
			page);
		state->register_page = page;
	}

	return 0;
}