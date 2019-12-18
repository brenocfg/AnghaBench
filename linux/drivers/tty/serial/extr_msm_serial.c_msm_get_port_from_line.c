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
struct uart_port {int dummy; } ;
struct TYPE_2__ {struct uart_port uart; } ;

/* Variables and functions */
 TYPE_1__* msm_uart_ports ; 

__attribute__((used)) static inline struct uart_port *msm_get_port_from_line(unsigned int line)
{
	return &msm_uart_ports[line].uart;
}