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
typedef  scalar_t__ u8 ;
struct i2c_client {int addr; } ;
struct adv748x_state {struct i2c_client** i2c_clients; } ;

/* Variables and functions */
 scalar_t__ ADV748X_IO_SLAVE_ADDR_BASE ; 
 unsigned int ADV748X_PAGE_DPLL ; 
 unsigned int ADV748X_PAGE_MAX ; 
 int /*<<< orphan*/  io_write (struct adv748x_state*,scalar_t__,int) ; 

__attribute__((used)) static int adv748x_set_slave_addresses(struct adv748x_state *state)
{
	struct i2c_client *client;
	unsigned int i;
	u8 io_reg;

	for (i = ADV748X_PAGE_DPLL; i < ADV748X_PAGE_MAX; ++i) {
		io_reg = ADV748X_IO_SLAVE_ADDR_BASE + i;
		client = state->i2c_clients[i];

		io_write(state, io_reg, client->addr << 1);
	}

	return 0;
}