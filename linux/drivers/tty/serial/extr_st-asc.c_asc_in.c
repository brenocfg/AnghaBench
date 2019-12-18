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
typedef  scalar_t__ u32 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 asc_in(struct uart_port *port, u32 offset)
{
#ifdef readl_relaxed
	return readl_relaxed(port->membase + offset);
#else
	return readl(port->membase + offset);
#endif
}