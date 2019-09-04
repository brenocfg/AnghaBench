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
struct adv748x_state {int /*<<< orphan*/ * endpoints; } ;

/* Variables and functions */
 unsigned int ADV748X_PORT_MAX ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adv748x_dt_cleanup(struct adv748x_state *state)
{
	unsigned int i;

	for (i = 0; i < ADV748X_PORT_MAX; i++)
		of_node_put(state->endpoints[i]);
}