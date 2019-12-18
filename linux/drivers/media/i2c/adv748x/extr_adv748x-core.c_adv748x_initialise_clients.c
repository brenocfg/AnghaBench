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
struct adv748x_state {int /*<<< orphan*/ * i2c_clients; int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ADV748X_PAGE_DPLL ; 
 unsigned int ADV748X_PAGE_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int adv748x_configure_regmap (struct adv748x_state*,unsigned int) ; 
 TYPE_1__* adv748x_default_addresses ; 
 int adv748x_set_slave_addresses (struct adv748x_state*) ; 
 int /*<<< orphan*/  adv_err (struct adv748x_state*,char*,unsigned int) ; 
 int /*<<< orphan*/  i2c_new_ancillary_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_initialise_clients(struct adv748x_state *state)
{
	unsigned int i;
	int ret;

	for (i = ADV748X_PAGE_DPLL; i < ADV748X_PAGE_MAX; ++i) {
		state->i2c_clients[i] = i2c_new_ancillary_device(
				state->client,
				adv748x_default_addresses[i].name,
				adv748x_default_addresses[i].default_addr);

		if (IS_ERR(state->i2c_clients[i])) {
			adv_err(state, "failed to create i2c client %u\n", i);
			return PTR_ERR(state->i2c_clients[i]);
		}

		ret = adv748x_configure_regmap(state, i);
		if (ret)
			return ret;
	}

	return adv748x_set_slave_addresses(state);
}