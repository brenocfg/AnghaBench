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
struct uart_port {int fifosize; } ;
struct qcom_geni_serial_port {int tx_fifo_depth; int tx_fifo_width; int /*<<< orphan*/  se; int /*<<< orphan*/  rx_fifo_depth; struct uart_port uport; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  geni_se_get_rx_fifo_depth (int /*<<< orphan*/ *) ; 
 int geni_se_get_tx_fifo_depth (int /*<<< orphan*/ *) ; 
 int geni_se_get_tx_fifo_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_tx_fifo_size(struct qcom_geni_serial_port *port)
{
	struct uart_port *uport;

	uport = &port->uport;
	port->tx_fifo_depth = geni_se_get_tx_fifo_depth(&port->se);
	port->tx_fifo_width = geni_se_get_tx_fifo_width(&port->se);
	port->rx_fifo_depth = geni_se_get_rx_fifo_depth(&port->se);
	uport->fifosize =
		(port->tx_fifo_depth * port->tx_fifo_width) / BITS_PER_BYTE;
}