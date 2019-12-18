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
struct uart_port {scalar_t__ membase; } ;
struct qcom_geni_serial_port {int rx_bytes_pw; int /*<<< orphan*/  (* handle_rx ) (struct uart_port*,int,int) ;} ;

/* Variables and functions */
 int RX_FIFO_WC_MSK ; 
 int RX_LAST ; 
 int RX_LAST_BYTE_VALID_MSK ; 
 int RX_LAST_BYTE_VALID_SHFT ; 
 scalar_t__ SE_GENI_RX_FIFO_STATUS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int,int) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 

__attribute__((used)) static void qcom_geni_serial_handle_rx(struct uart_port *uport, bool drop)
{
	u32 status;
	u32 word_cnt;
	u32 last_word_byte_cnt;
	u32 last_word_partial;
	u32 total_bytes;
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);

	status = readl(uport->membase +	SE_GENI_RX_FIFO_STATUS);
	word_cnt = status & RX_FIFO_WC_MSK;
	last_word_partial = status & RX_LAST;
	last_word_byte_cnt = (status & RX_LAST_BYTE_VALID_MSK) >>
						RX_LAST_BYTE_VALID_SHFT;

	if (!word_cnt)
		return;
	total_bytes = port->rx_bytes_pw * (word_cnt - 1);
	if (last_word_partial && last_word_byte_cnt)
		total_bytes += last_word_byte_cnt;
	else
		total_bytes += port->rx_bytes_pw;
	port->handle_rx(uport, total_bytes, drop);
}