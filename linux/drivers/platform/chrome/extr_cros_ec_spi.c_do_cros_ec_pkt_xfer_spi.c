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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  trans_delay ;
typedef  int /*<<< orphan*/  trans ;
struct spi_transfer {scalar_t__* rx_buf; int len; int cs_change; int /*<<< orphan*/  tx_buf; scalar_t__ delay_usecs; } ;
struct spi_message {int dummy; } ;
struct ec_host_response {int data_len; int /*<<< orphan*/  result; } ;
struct cros_ec_spi {unsigned long last_transfer_ns; TYPE_1__* spi; scalar_t__ start_of_msg_delay; } ;
struct cros_ec_device {int /*<<< orphan*/  dev; scalar_t__* din; int /*<<< orphan*/  dout; struct cros_ec_spi* priv; } ;
struct cros_ec_command {int insize; scalar_t__ command; scalar_t__* data; int /*<<< orphan*/  result; } ;
struct TYPE_2__ {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADMSG ; 
 scalar_t__ EC_CMD_REBOOT_EC ; 
 int /*<<< orphan*/  EC_REBOOT_DELAY_MS ; 
 scalar_t__ EC_SPI_NOT_READY ; 
 scalar_t__ EC_SPI_PAST_END ; 
 unsigned long EC_SPI_RECOVERY_TIME_NS ; 
 scalar_t__ EC_SPI_RX_BAD_DATA ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cros_ec_check_result (struct cros_ec_device*,struct cros_ec_command*) ; 
 int cros_ec_prepare_tx (struct cros_ec_device*,struct cros_ec_command*) ; 
 int cros_ec_spi_receive_packet (struct cros_ec_device*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 unsigned long ktime_get_ns () ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndelay (unsigned long) ; 
 int /*<<< orphan*/  spi_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync_locked (TYPE_1__*,struct spi_message*) ; 
 int terminate_request (struct cros_ec_device*) ; 

__attribute__((used)) static int do_cros_ec_pkt_xfer_spi(struct cros_ec_device *ec_dev,
				   struct cros_ec_command *ec_msg)
{
	struct ec_host_response *response;
	struct cros_ec_spi *ec_spi = ec_dev->priv;
	struct spi_transfer trans, trans_delay;
	struct spi_message msg;
	int i, len;
	u8 *ptr;
	u8 *rx_buf;
	u8 sum;
	u8 rx_byte;
	int ret = 0, final_ret;
	unsigned long delay;

	len = cros_ec_prepare_tx(ec_dev, ec_msg);
	dev_dbg(ec_dev->dev, "prepared, len=%d\n", len);

	/* If it's too soon to do another transaction, wait */
	delay = ktime_get_ns() - ec_spi->last_transfer_ns;
	if (delay < EC_SPI_RECOVERY_TIME_NS)
		ndelay(EC_SPI_RECOVERY_TIME_NS - delay);

	rx_buf = kzalloc(len, GFP_KERNEL);
	if (!rx_buf)
		return -ENOMEM;

	spi_bus_lock(ec_spi->spi->master);

	/*
	 * Leave a gap between CS assertion and clocking of data to allow the
	 * EC time to wakeup.
	 */
	spi_message_init(&msg);
	if (ec_spi->start_of_msg_delay) {
		memset(&trans_delay, 0, sizeof(trans_delay));
		trans_delay.delay_usecs = ec_spi->start_of_msg_delay;
		spi_message_add_tail(&trans_delay, &msg);
	}

	/* Transmit phase - send our message */
	memset(&trans, 0, sizeof(trans));
	trans.tx_buf = ec_dev->dout;
	trans.rx_buf = rx_buf;
	trans.len = len;
	trans.cs_change = 1;
	spi_message_add_tail(&trans, &msg);
	ret = spi_sync_locked(ec_spi->spi, &msg);

	/* Get the response */
	if (!ret) {
		/* Verify that EC can process command */
		for (i = 0; i < len; i++) {
			rx_byte = rx_buf[i];
			/*
			 * Seeing the PAST_END, RX_BAD_DATA, or NOT_READY
			 * markers are all signs that the EC didn't fully
			 * receive our command. e.g., if the EC is flashing
			 * itself, it can't respond to any commands and instead
			 * clocks out EC_SPI_PAST_END from its SPI hardware
			 * buffer. Similar occurrences can happen if the AP is
			 * too slow to clock out data after asserting CS -- the
			 * EC will abort and fill its buffer with
			 * EC_SPI_RX_BAD_DATA.
			 *
			 * In all cases, these errors should be safe to retry.
			 * Report -EAGAIN and let the caller decide what to do
			 * about that.
			 */
			if (rx_byte == EC_SPI_PAST_END  ||
			    rx_byte == EC_SPI_RX_BAD_DATA ||
			    rx_byte == EC_SPI_NOT_READY) {
				ret = -EAGAIN;
				break;
			}
		}
	}

	if (!ret)
		ret = cros_ec_spi_receive_packet(ec_dev,
				ec_msg->insize + sizeof(*response));
	else if (ret != -EAGAIN)
		dev_err(ec_dev->dev, "spi transfer failed: %d\n", ret);

	final_ret = terminate_request(ec_dev);

	spi_bus_unlock(ec_spi->spi->master);

	if (!ret)
		ret = final_ret;
	if (ret < 0)
		goto exit;

	ptr = ec_dev->din;

	/* check response error code */
	response = (struct ec_host_response *)ptr;
	ec_msg->result = response->result;

	ret = cros_ec_check_result(ec_dev, ec_msg);
	if (ret)
		goto exit;

	len = response->data_len;
	sum = 0;
	if (len > ec_msg->insize) {
		dev_err(ec_dev->dev, "packet too long (%d bytes, expected %d)",
			len, ec_msg->insize);
		ret = -EMSGSIZE;
		goto exit;
	}

	for (i = 0; i < sizeof(*response); i++)
		sum += ptr[i];

	/* copy response packet payload and compute checksum */
	memcpy(ec_msg->data, ptr + sizeof(*response), len);
	for (i = 0; i < len; i++)
		sum += ec_msg->data[i];

	if (sum) {
		dev_err(ec_dev->dev,
			"bad packet checksum, calculated %x\n",
			sum);
		ret = -EBADMSG;
		goto exit;
	}

	ret = len;
exit:
	kfree(rx_buf);
	if (ec_msg->command == EC_CMD_REBOOT_EC)
		msleep(EC_REBOOT_DELAY_MS);

	return ret;
}