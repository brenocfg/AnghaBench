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
struct ehv_bc_data {int /*<<< orphan*/  rx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehv_bc_tty_unthrottle(struct tty_struct *ttys)
{
	struct ehv_bc_data *bc = ttys->driver_data;

	/* If there is any data in the queue when the RX interrupt is enabled,
	 * we'll immediately get an RX interrupt.
	 */
	enable_irq(bc->rx_irq);
}