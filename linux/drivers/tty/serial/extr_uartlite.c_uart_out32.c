#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct uartlite_data {TYPE_1__* reg_ops; } ;
struct uart_port {scalar_t__ membase; struct uartlite_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* out ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void uart_out32(u32 val, u32 offset, struct uart_port *port)
{
	struct uartlite_data *pdata = port->private_data;

	pdata->reg_ops->out(val, port->membase + offset);
}