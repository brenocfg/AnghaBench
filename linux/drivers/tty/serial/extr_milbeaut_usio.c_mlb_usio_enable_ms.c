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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ MLB_USIO_REG_SCR ; 
 int MLB_USIO_SCR_RIE ; 
 int MLB_USIO_SCR_RXE ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void mlb_usio_enable_ms(struct uart_port *port)
{
	writeb(readb(port->membase + MLB_USIO_REG_SCR) |
	       MLB_USIO_SCR_RIE | MLB_USIO_SCR_RXE,
	       port->membase + MLB_USIO_REG_SCR);
}