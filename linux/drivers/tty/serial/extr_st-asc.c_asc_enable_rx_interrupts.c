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
 int /*<<< orphan*/  ASC_INTEN ; 
 int ASC_INTEN_RBE ; 
 int asc_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asc_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void asc_enable_rx_interrupts(struct uart_port *port)
{
	u32 intenable = asc_in(port, ASC_INTEN) | ASC_INTEN_RBE;
	asc_out(port, ASC_INTEN, intenable);
}