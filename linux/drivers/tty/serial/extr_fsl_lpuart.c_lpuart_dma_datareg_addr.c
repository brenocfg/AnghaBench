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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int iotype; scalar_t__ mapbase; } ;
struct lpuart_port {TYPE_1__ port; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ UARTDATA ; 
 scalar_t__ UARTDR ; 
#define  UPIO_MEM32 129 
#define  UPIO_MEM32BE 128 

__attribute__((used)) static dma_addr_t lpuart_dma_datareg_addr(struct lpuart_port *sport)
{
	switch (sport->port.iotype) {
	case UPIO_MEM32:
		return sport->port.mapbase + UARTDATA;
	case UPIO_MEM32BE:
		return sport->port.mapbase + UARTDATA + sizeof(u32) - 1;
	}
	return sport->port.mapbase + UARTDR;
}