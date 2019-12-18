#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxser_port {scalar_t__ type; int rx_trigger; int rx_high_water; int rx_low_water; int xmit_fifo_size; TYPE_1__* board; } ;
struct TYPE_4__ {scalar_t__ type; int rx_trigger; int rx_low_water; int rx_high_water; int xmit_fifo_size; } ;
struct TYPE_3__ {scalar_t__ chip_flag; } ;

/* Variables and functions */
 TYPE_2__* Gpci_uart_info ; 
 scalar_t__ PORT_16450 ; 
 scalar_t__ PORT_8250 ; 
 int UART_INFO_NUM ; 

__attribute__((used)) static void process_txrx_fifo(struct mxser_port *info)
{
	int i;

	if ((info->type == PORT_16450) || (info->type == PORT_8250)) {
		info->rx_trigger = 1;
		info->rx_high_water = 1;
		info->rx_low_water = 1;
		info->xmit_fifo_size = 1;
	} else
		for (i = 0; i < UART_INFO_NUM; i++)
			if (info->board->chip_flag == Gpci_uart_info[i].type) {
				info->rx_trigger = Gpci_uart_info[i].rx_trigger;
				info->rx_low_water = Gpci_uart_info[i].rx_low_water;
				info->rx_high_water = Gpci_uart_info[i].rx_high_water;
				info->xmit_fifo_size = Gpci_uart_info[i].xmit_fifo_size;
				break;
			}
}