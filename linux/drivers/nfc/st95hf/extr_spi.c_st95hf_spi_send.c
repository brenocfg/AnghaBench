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
struct st95hf_spi_context {int req_issync; int /*<<< orphan*/  spi_lock; int /*<<< orphan*/  done; struct spi_device* spidev; } ;
struct spi_transfer {unsigned char* tx_buf; int len; } ;
struct spi_message {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum req_type { ____Placeholder_req_type } req_type ;

/* Variables and functions */
 int ASYNC ; 
 int ETIMEDOUT ; 
 int SYNC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int st95hf_spi_send(struct st95hf_spi_context *spicontext,
		    unsigned char *buffertx,
		    int datalen,
		    enum req_type reqtype)
{
	struct spi_message m;
	int result = 0;
	struct spi_device *spidev = spicontext->spidev;
	struct spi_transfer tx_transfer = {
		.tx_buf = buffertx,
		.len = datalen,
	};

	mutex_lock(&spicontext->spi_lock);

	if (reqtype == SYNC) {
		spicontext->req_issync = true;
		reinit_completion(&spicontext->done);
	} else {
		spicontext->req_issync = false;
	}

	spi_message_init(&m);
	spi_message_add_tail(&tx_transfer, &m);

	result = spi_sync(spidev, &m);
	if (result) {
		dev_err(&spidev->dev, "error: sending cmd to st95hf using SPI = %d\n",
			result);
		mutex_unlock(&spicontext->spi_lock);
		return result;
	}

	/* return for asynchronous or no-wait case */
	if (reqtype == ASYNC) {
		mutex_unlock(&spicontext->spi_lock);
		return 0;
	}

	result = wait_for_completion_timeout(&spicontext->done,
					     msecs_to_jiffies(1000));
	/* check for timeout or success */
	if (!result) {
		dev_err(&spidev->dev, "error: response not ready timeout\n");
		result = -ETIMEDOUT;
	} else {
		result = 0;
	}

	mutex_unlock(&spicontext->spi_lock);

	return result;
}