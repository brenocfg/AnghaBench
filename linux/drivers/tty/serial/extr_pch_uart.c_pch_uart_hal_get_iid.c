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
struct eg20t_port {scalar_t__ membase; } ;

/* Variables and functions */
 unsigned char PCH_UART_IIR_IID ; 
 unsigned char PCH_UART_IIR_IP ; 
 unsigned char PCH_UART_IIR_TOI ; 
 scalar_t__ UART_IIR ; 
 unsigned char ioread8 (scalar_t__) ; 

__attribute__((used)) static unsigned char pch_uart_hal_get_iid(struct eg20t_port *priv)
{
	return ioread8(priv->membase + UART_IIR) &\
		      (PCH_UART_IIR_IID | PCH_UART_IIR_TOI | PCH_UART_IIR_IP);
}