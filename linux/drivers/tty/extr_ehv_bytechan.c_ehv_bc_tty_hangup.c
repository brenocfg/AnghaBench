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
struct tty_struct {struct ehv_bc_data* driver_data; } ;
struct ehv_bc_data {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehv_bc_tx_dequeue (struct ehv_bc_data*) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehv_bc_tty_hangup(struct tty_struct *ttys)
{
	struct ehv_bc_data *bc = ttys->driver_data;

	ehv_bc_tx_dequeue(bc);
	tty_port_hangup(&bc->port);
}