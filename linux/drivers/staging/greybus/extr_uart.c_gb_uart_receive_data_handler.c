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
typedef  int u16 ;
struct tty_port {int dummy; } ;
struct gb_uart_recv_data_request {int flags; int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct gb_tty {TYPE_1__* gbphy_dev; struct tty_port port; } ;
struct gb_operation {struct gb_message* request; struct gb_connection* connection; } ;
struct gb_message {int payload_size; struct gb_uart_recv_data_request* payload; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int GB_UART_RECV_FLAG_BREAK ; 
 int GB_UART_RECV_FLAG_FRAMING ; 
 int GB_UART_RECV_FLAG_OVERRUN ; 
 int GB_UART_RECV_FLAG_PARITY ; 
 unsigned long TTY_BREAK ; 
 unsigned long TTY_FRAME ; 
 unsigned long TTY_NORMAL ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 unsigned long TTY_PARITY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct gb_tty* gb_connection_get_data (struct gb_connection*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tty_insert_flip_string_fixed_flag (struct tty_port*,int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static int gb_uart_receive_data_handler(struct gb_operation *op)
{
	struct gb_connection *connection = op->connection;
	struct gb_tty *gb_tty = gb_connection_get_data(connection);
	struct tty_port *port = &gb_tty->port;
	struct gb_message *request = op->request;
	struct gb_uart_recv_data_request *receive_data;
	u16 recv_data_size;
	int count;
	unsigned long tty_flags = TTY_NORMAL;

	if (request->payload_size < sizeof(*receive_data)) {
		dev_err(&gb_tty->gbphy_dev->dev,
			"short receive-data request received (%zu < %zu)\n",
			request->payload_size, sizeof(*receive_data));
		return -EINVAL;
	}

	receive_data = op->request->payload;
	recv_data_size = le16_to_cpu(receive_data->size);

	if (recv_data_size != request->payload_size - sizeof(*receive_data)) {
		dev_err(&gb_tty->gbphy_dev->dev,
			"malformed receive-data request received (%u != %zu)\n",
			recv_data_size,
			request->payload_size - sizeof(*receive_data));
		return -EINVAL;
	}

	if (!recv_data_size)
		return -EINVAL;

	if (receive_data->flags) {
		if (receive_data->flags & GB_UART_RECV_FLAG_BREAK)
			tty_flags = TTY_BREAK;
		else if (receive_data->flags & GB_UART_RECV_FLAG_PARITY)
			tty_flags = TTY_PARITY;
		else if (receive_data->flags & GB_UART_RECV_FLAG_FRAMING)
			tty_flags = TTY_FRAME;

		/* overrun is special, not associated with a char */
		if (receive_data->flags & GB_UART_RECV_FLAG_OVERRUN)
			tty_insert_flip_char(port, 0, TTY_OVERRUN);
	}
	count = tty_insert_flip_string_fixed_flag(port, receive_data->data,
						  tty_flags, recv_data_size);
	if (count != recv_data_size) {
		dev_err(&gb_tty->gbphy_dev->dev,
			"UART: RX 0x%08x bytes only wrote 0x%08x\n",
			recv_data_size, count);
	}
	if (count)
		tty_flip_buffer_push(port);
	return 0;
}