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
struct s3c24xx_uart_info {int dummy; } ;
struct TYPE_2__ {struct s3c24xx_uart_info* info; } ;

/* Variables and functions */
 TYPE_1__* to_ourport (struct uart_port*) ; 

__attribute__((used)) static inline struct s3c24xx_uart_info
	*s3c24xx_port_to_info(struct uart_port *port)
{
	return to_ourport(port)->info;
}