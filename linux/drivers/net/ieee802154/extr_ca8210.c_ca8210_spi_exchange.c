#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {struct ca8210_priv* driver_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct ca8210_priv {int* sync_command_response; int /*<<< orphan*/  sync_exchange_complete; int /*<<< orphan*/  spi_transfer_complete; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int CA8210_SYNC_TIMEOUT ; 
 int EBUSY ; 
 long ERESTARTSYS ; 
 int ETIME ; 
 int const SPI_SYN ; 
 int ca8210_spi_transfer (int /*<<< orphan*/ ,int const*,size_t) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca8210_spi_exchange(
	const u8 *buf,
	size_t len,
	u8 *response,
	void *device_ref
)
{
	int status = 0;
	struct spi_device *spi = device_ref;
	struct ca8210_priv *priv = spi->dev.driver_data;
	long wait_remaining;

	if ((buf[0] & SPI_SYN) && response) { /* if sync wait for confirm */
		reinit_completion(&priv->sync_exchange_complete);
		priv->sync_command_response = response;
	}

	do {
		reinit_completion(&priv->spi_transfer_complete);
		status = ca8210_spi_transfer(priv->spi, buf, len);
		if (status) {
			dev_warn(
				&spi->dev,
				"spi write failed, returned %d\n",
				status
			);
			if (status == -EBUSY)
				continue;
			if (((buf[0] & SPI_SYN) && response))
				complete(&priv->sync_exchange_complete);
			goto cleanup;
		}

		wait_remaining = wait_for_completion_interruptible_timeout(
			&priv->spi_transfer_complete,
			msecs_to_jiffies(1000)
		);
		if (wait_remaining == -ERESTARTSYS) {
			status = -ERESTARTSYS;
		} else if (wait_remaining == 0) {
			dev_err(
				&spi->dev,
				"SPI downstream transfer timed out!\n"
			);
			status = -ETIME;
			goto cleanup;
		}
	} while (status < 0);

	if (!((buf[0] & SPI_SYN) && response))
		goto cleanup;

	wait_remaining = wait_for_completion_interruptible_timeout(
		&priv->sync_exchange_complete,
		msecs_to_jiffies(CA8210_SYNC_TIMEOUT)
	);
	if (wait_remaining == -ERESTARTSYS) {
		status = -ERESTARTSYS;
	} else if (wait_remaining == 0) {
		dev_err(
			&spi->dev,
			"Synchronous confirm timeout\n"
		);
		status = -ETIME;
	}

cleanup:
	priv->sync_command_response = NULL;
	return status;
}