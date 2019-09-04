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
struct serio {struct ps2if* port_data; } ;
struct ps2if {int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; scalar_t__ open; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PS2CR ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ps2if*) ; 
 int /*<<< orphan*/  sa1111_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ps2_close(struct serio *io)
{
	struct ps2if *ps2if = io->port_data;

	writel_relaxed(0, ps2if->base + PS2CR);

	disable_irq_wake(ps2if->rx_irq);

	ps2if->open = 0;

	free_irq(ps2if->tx_irq, ps2if);
	free_irq(ps2if->rx_irq, ps2if);

	sa1111_disable_device(ps2if->dev);
}