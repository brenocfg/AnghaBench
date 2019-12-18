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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct clps711x_port {int /*<<< orphan*/  syscon; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSCON_OFFSET ; 
 int /*<<< orphan*/  SYSCON_UARTEN ; 
 struct clps711x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uart_clps711x_shutdown(struct uart_port *port)
{
	struct clps711x_port *s = dev_get_drvdata(port->dev);

	/* Disable the port */
	regmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON_UARTEN, 0);
}