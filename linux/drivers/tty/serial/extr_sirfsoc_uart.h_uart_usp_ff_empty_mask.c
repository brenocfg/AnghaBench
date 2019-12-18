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
struct uart_port {int /*<<< orphan*/  fifosize; } ;

/* Variables and functions */
 int ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 uart_usp_ff_empty_mask(struct uart_port *port)
{
	u32 empty_bit;

	empty_bit = ilog2(port->fifosize) + 1;
	return (1 << empty_bit);
}