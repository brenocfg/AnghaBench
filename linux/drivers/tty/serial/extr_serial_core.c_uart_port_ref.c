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
struct uart_state {struct uart_port* uart_port; int /*<<< orphan*/  refcount; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct uart_port *uart_port_ref(struct uart_state *state)
{
	if (atomic_add_unless(&state->refcount, 1, 0))
		return state->uart_port;
	return NULL;
}