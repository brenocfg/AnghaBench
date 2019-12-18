#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gbphy_device_id {int dummy; } ;
struct gbphy_device {int /*<<< orphan*/  dev; TYPE_1__* cport_desc; int /*<<< orphan*/  bundle; } ;
struct gb_uart_send_data_request {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_6__ {int data_bits; int /*<<< orphan*/  parity; int /*<<< orphan*/  format; int /*<<< orphan*/  rate; } ;
struct gb_tty {size_t buffer_payload_max; int minor; struct gb_tty* buffer; int /*<<< orphan*/  write_fifo; TYPE_3__ port; TYPE_2__ line_coding; int /*<<< orphan*/  ctrlout; struct gbphy_device* gbphy_dev; struct gb_connection* connection; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wioctl; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  credits_complete; int /*<<< orphan*/  credits; int /*<<< orphan*/  tx_work; } ;
struct gb_connection {int dummy; } ;
typedef  struct gb_connection device ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GB_SERIAL_1_STOP_BITS ; 
 int /*<<< orphan*/  GB_SERIAL_NO_PARITY ; 
 int /*<<< orphan*/  GB_UART_FIRMWARE_CREDITS ; 
 int /*<<< orphan*/  GB_UART_WRITE_FIFO_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int alloc_minor (struct gb_tty*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gb_connection* gb_connection_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int gb_connection_enable_tx (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_tty*) ; 
 int /*<<< orphan*/  gb_gbphy_set_data (struct gbphy_device*,struct gb_tty*) ; 
 size_t gb_operation_get_payload_size_max (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_port_ops ; 
 int /*<<< orphan*/  gb_tty_driver ; 
 int /*<<< orphan*/  gb_uart_request_handler ; 
 int /*<<< orphan*/  gb_uart_tx_write_work ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (struct gbphy_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gb_tty*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_minor (struct gb_tty*) ; 
 int /*<<< orphan*/  send_control (struct gb_tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_line_coding (struct gb_tty*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_3__*) ; 
 struct gb_connection* tty_port_register_device (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_uart_probe(struct gbphy_device *gbphy_dev,
			 const struct gbphy_device_id *id)
{
	struct gb_connection *connection;
	size_t max_payload;
	struct gb_tty *gb_tty;
	struct device *tty_dev;
	int retval;
	int minor;

	gb_tty = kzalloc(sizeof(*gb_tty), GFP_KERNEL);
	if (!gb_tty)
		return -ENOMEM;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  gb_uart_request_handler);
	if (IS_ERR(connection)) {
		retval = PTR_ERR(connection);
		goto exit_tty_free;
	}

	max_payload = gb_operation_get_payload_size_max(connection);
	if (max_payload < sizeof(struct gb_uart_send_data_request)) {
		retval = -EINVAL;
		goto exit_connection_destroy;
	}

	gb_tty->buffer_payload_max = max_payload -
			sizeof(struct gb_uart_send_data_request);

	gb_tty->buffer = kzalloc(gb_tty->buffer_payload_max, GFP_KERNEL);
	if (!gb_tty->buffer) {
		retval = -ENOMEM;
		goto exit_connection_destroy;
	}

	INIT_WORK(&gb_tty->tx_work, gb_uart_tx_write_work);

	retval = kfifo_alloc(&gb_tty->write_fifo, GB_UART_WRITE_FIFO_SIZE,
			     GFP_KERNEL);
	if (retval)
		goto exit_buf_free;

	gb_tty->credits = GB_UART_FIRMWARE_CREDITS;
	init_completion(&gb_tty->credits_complete);

	minor = alloc_minor(gb_tty);
	if (minor < 0) {
		if (minor == -ENOSPC) {
			dev_err(&gbphy_dev->dev,
				"no more free minor numbers\n");
			retval = -ENODEV;
		} else {
			retval = minor;
		}
		goto exit_kfifo_free;
	}

	gb_tty->minor = minor;
	spin_lock_init(&gb_tty->write_lock);
	spin_lock_init(&gb_tty->read_lock);
	init_waitqueue_head(&gb_tty->wioctl);
	mutex_init(&gb_tty->mutex);

	tty_port_init(&gb_tty->port);
	gb_tty->port.ops = &gb_port_ops;

	gb_tty->connection = connection;
	gb_tty->gbphy_dev = gbphy_dev;
	gb_connection_set_data(connection, gb_tty);
	gb_gbphy_set_data(gbphy_dev, gb_tty);

	retval = gb_connection_enable_tx(connection);
	if (retval)
		goto exit_release_minor;

	send_control(gb_tty, gb_tty->ctrlout);

	/* initialize the uart to be 9600n81 */
	gb_tty->line_coding.rate = cpu_to_le32(9600);
	gb_tty->line_coding.format = GB_SERIAL_1_STOP_BITS;
	gb_tty->line_coding.parity = GB_SERIAL_NO_PARITY;
	gb_tty->line_coding.data_bits = 8;
	send_line_coding(gb_tty);

	retval = gb_connection_enable(connection);
	if (retval)
		goto exit_connection_disable;

	tty_dev = tty_port_register_device(&gb_tty->port, gb_tty_driver, minor,
					   &gbphy_dev->dev);
	if (IS_ERR(tty_dev)) {
		retval = PTR_ERR(tty_dev);
		goto exit_connection_disable;
	}

	gbphy_runtime_put_autosuspend(gbphy_dev);
	return 0;

exit_connection_disable:
	gb_connection_disable(connection);
exit_release_minor:
	release_minor(gb_tty);
exit_kfifo_free:
	kfifo_free(&gb_tty->write_fifo);
exit_buf_free:
	kfree(gb_tty->buffer);
exit_connection_destroy:
	gb_connection_destroy(connection);
exit_tty_free:
	kfree(gb_tty);

	return retval;
}