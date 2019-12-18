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
struct st95hf_spi_context {int /*<<< orphan*/  spi_lock; struct spi_device* spidev; } ;
struct spi_transfer {unsigned char* tx_buf; int len; unsigned char* rx_buf; int cs_change; } ;
struct spi_message {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char ST95HF_COMMAND_RECEIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

int st95hf_spi_recv_response(struct st95hf_spi_context *spicontext,
			     unsigned char *receivebuff)
{
	int len = 0;
	struct spi_transfer tx_takedata;
	struct spi_message m;
	struct spi_device *spidev = spicontext->spidev;
	unsigned char readdata_cmd = ST95HF_COMMAND_RECEIVE;
	struct spi_transfer t[2] = {
		{.tx_buf = &readdata_cmd, .len = 1,},
		{.rx_buf = receivebuff, .len = 2, .cs_change = 1,},
	};

	int ret = 0;

	memset(&tx_takedata, 0x0, sizeof(struct spi_transfer));

	mutex_lock(&spicontext->spi_lock);

	/* First spi transfer to know the length of valid data */
	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);

	ret = spi_sync(spidev, &m);
	if (ret) {
		dev_err(&spidev->dev, "spi_recv_resp, data length error = %d\n",
			ret);
		mutex_unlock(&spicontext->spi_lock);
		return ret;
	}

	/* As 2 bytes are already read */
	len = 2;

	/* Support of long frame */
	if (receivebuff[0] & 0x60)
		len += (((receivebuff[0] & 0x60) >> 5) << 8) | receivebuff[1];
	else
		len += receivebuff[1];

	/* Now make a transfer to read only relevant bytes */
	tx_takedata.rx_buf = &receivebuff[2];
	tx_takedata.len = len - 2;

	spi_message_init(&m);
	spi_message_add_tail(&tx_takedata, &m);

	ret = spi_sync(spidev, &m);

	mutex_unlock(&spicontext->spi_lock);
	if (ret) {
		dev_err(&spidev->dev, "spi_recv_resp, data read error = %d\n",
			ret);
		return ret;
	}

	return len;
}