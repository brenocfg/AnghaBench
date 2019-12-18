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
typedef  int u32 ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_CTL2 ; 
 int THLD_RX_FULL_MASK ; 
 int serial_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sprd_rx_full_thld(struct uart_port *port, u32 thld)
{
	u32 val = serial_in(port, SPRD_CTL2);

	val &= ~THLD_RX_FULL_MASK;
	val |= thld & THLD_RX_FULL_MASK;
	serial_out(port, SPRD_CTL2, val);
}