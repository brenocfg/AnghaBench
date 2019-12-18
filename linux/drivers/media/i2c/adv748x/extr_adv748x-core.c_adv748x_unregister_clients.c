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
struct adv748x_state {int /*<<< orphan*/ * i2c_clients; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adv748x_unregister_clients(struct adv748x_state *state)
{
	unsigned int i;

	for (i = 1; i < ARRAY_SIZE(state->i2c_clients); ++i)
		i2c_unregister_device(state->i2c_clients[i]);
}