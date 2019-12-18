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
typedef  int /*<<< orphan*/  u8 ;
struct eg20t_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ UART_LSR ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 

__attribute__((used)) static u8 pch_uart_hal_get_line_status(struct eg20t_port *priv)
{
	return ioread8(priv->membase + UART_LSR);
}