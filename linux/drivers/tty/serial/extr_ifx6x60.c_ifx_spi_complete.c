#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  srdy; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; } ;
struct ifx_spi_device {unsigned char spi_slave_cts; int /*<<< orphan*/  tty_port; scalar_t__ spi_more; int /*<<< orphan*/  io_work_tasklet; int /*<<< orphan*/  flags; TYPE_3__ gpio; int /*<<< orphan*/  tx_fifo; scalar_t__ write_pending; TYPE_2__ spi_msg; TYPE_1__* spi_dev; int /*<<< orphan*/ * rx_buffer; int /*<<< orphan*/  (* swap_buf ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IFX_SPI_HEADER_0 ; 
 int IFX_SPI_HEADER_F ; 
 size_t IFX_SPI_HEADER_OVERHEAD ; 
 int /*<<< orphan*/  IFX_SPI_POWER_DATA_PENDING ; 
 int /*<<< orphan*/  IFX_SPI_POWER_SRDY ; 
 int /*<<< orphan*/  IFX_SPI_STATE_IO_IN_PROGRESS ; 
 int /*<<< orphan*/  IFX_SPI_STATE_IO_READY ; 
 size_t IFX_SPI_TRANSFER_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int ifx_spi_decode_spi_header (int /*<<< orphan*/ *,int*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  ifx_spi_insert_flip_string (struct ifx_spi_device*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ifx_spi_power_state_clear (struct ifx_spi_device*,int /*<<< orphan*/ ) ; 
 int kfifo_len (int /*<<< orphan*/ *) ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrdy_assert (struct ifx_spi_device*) ; 
 int /*<<< orphan*/  mrdy_set_low (struct ifx_spi_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ifx_spi_complete(void *ctx)
{
	struct ifx_spi_device *ifx_dev = ctx;
	int length;
	int actual_length;
	unsigned char more = 0;
	unsigned char cts;
	int local_write_pending = 0;
	int queue_length;
	int srdy;
	int decode_result;

	mrdy_set_low(ifx_dev);

	if (!ifx_dev->spi_msg.status) {
		/* check header validity, get comm flags */
		ifx_dev->swap_buf(ifx_dev->rx_buffer, IFX_SPI_HEADER_OVERHEAD,
			&ifx_dev->rx_buffer[IFX_SPI_HEADER_OVERHEAD]);
		decode_result = ifx_spi_decode_spi_header(ifx_dev->rx_buffer,
				&length, &more, &cts);
		if (decode_result == IFX_SPI_HEADER_0) {
			dev_dbg(&ifx_dev->spi_dev->dev,
				"ignore input: invalid header 0");
			ifx_dev->spi_slave_cts = 0;
			goto complete_exit;
		} else if (decode_result == IFX_SPI_HEADER_F) {
			dev_dbg(&ifx_dev->spi_dev->dev,
				"ignore input: invalid header F");
			goto complete_exit;
		}

		ifx_dev->spi_slave_cts = cts;

		actual_length = min((unsigned int)length,
					ifx_dev->spi_msg.actual_length);
		ifx_dev->swap_buf(
			(ifx_dev->rx_buffer + IFX_SPI_HEADER_OVERHEAD),
			 actual_length,
			 &ifx_dev->rx_buffer[IFX_SPI_TRANSFER_SIZE]);
		ifx_spi_insert_flip_string(
			ifx_dev,
			ifx_dev->rx_buffer + IFX_SPI_HEADER_OVERHEAD,
			(size_t)actual_length);
	} else {
		more = 0;
		dev_dbg(&ifx_dev->spi_dev->dev, "SPI transfer error %d",
		       ifx_dev->spi_msg.status);
	}

complete_exit:
	if (ifx_dev->write_pending) {
		ifx_dev->write_pending = 0;
		local_write_pending = 1;
	}

	clear_bit(IFX_SPI_STATE_IO_IN_PROGRESS, &(ifx_dev->flags));

	queue_length = kfifo_len(&ifx_dev->tx_fifo);
	srdy = gpio_get_value(ifx_dev->gpio.srdy);
	if (!srdy)
		ifx_spi_power_state_clear(ifx_dev, IFX_SPI_POWER_SRDY);

	/* schedule output if there is more to do */
	if (test_and_clear_bit(IFX_SPI_STATE_IO_READY, &ifx_dev->flags))
		tasklet_schedule(&ifx_dev->io_work_tasklet);
	else {
		if (more || ifx_dev->spi_more || queue_length > 0 ||
			local_write_pending) {
			if (ifx_dev->spi_slave_cts) {
				if (more)
					mrdy_assert(ifx_dev);
			} else
				mrdy_assert(ifx_dev);
		} else {
			/*
			 * poke line discipline driver if any for more data
			 * may or may not get more data to write
			 * for now, say not busy
			 */
			ifx_spi_power_state_clear(ifx_dev,
						  IFX_SPI_POWER_DATA_PENDING);
			tty_port_tty_wakeup(&ifx_dev->tty_port);
		}
	}
}