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
struct uart_txx9_port {int dummy; } ;

/* Variables and functions */
 unsigned int sio_in (struct uart_txx9_port*,int) ; 
 int /*<<< orphan*/  sio_out (struct uart_txx9_port*,int,unsigned int) ; 

__attribute__((used)) static inline void
sio_mask(struct uart_txx9_port *up, int offset, unsigned int value)
{
	sio_out(up, offset, sio_in(up, offset) & ~value);
}