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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX310X_LCR_REG ; 
 int /*<<< orphan*/  MAX310X_LCR_TXBREAK_BIT ; 
 int /*<<< orphan*/  max310x_port_update (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max310x_break_ctl(struct uart_port *port, int break_state)
{
	max310x_port_update(port, MAX310X_LCR_REG,
			    MAX310X_LCR_TXBREAK_BIT,
			    break_state ? MAX310X_LCR_TXBREAK_BIT : 0);
}