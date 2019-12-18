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
struct spi_transfer {long long len; int /*<<< orphan*/  speed_hz; } ;
struct spi_statistics {int dummy; } ;
struct spi_message {TYPE_1__* spi; } ;
struct spi_controller {int /*<<< orphan*/  xfer_completion; struct spi_statistics statistics; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct spi_statistics statistics; } ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SPI_STATISTICS_INCREMENT_FIELD (struct spi_statistics*,int /*<<< orphan*/ ) ; 
 unsigned long long UINT_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long long) ; 
 scalar_t__ spi_controller_is_slave (struct spi_controller*) ; 
 int /*<<< orphan*/  timedout ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 
 unsigned long long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_transfer_wait(struct spi_controller *ctlr,
			     struct spi_message *msg,
			     struct spi_transfer *xfer)
{
	struct spi_statistics *statm = &ctlr->statistics;
	struct spi_statistics *stats = &msg->spi->statistics;
	unsigned long long ms = 1;

	if (spi_controller_is_slave(ctlr)) {
		if (wait_for_completion_interruptible(&ctlr->xfer_completion)) {
			dev_dbg(&msg->spi->dev, "SPI transfer interrupted\n");
			return -EINTR;
		}
	} else {
		ms = 8LL * 1000LL * xfer->len;
		do_div(ms, xfer->speed_hz);
		ms += ms + 200; /* some tolerance */

		if (ms > UINT_MAX)
			ms = UINT_MAX;

		ms = wait_for_completion_timeout(&ctlr->xfer_completion,
						 msecs_to_jiffies(ms));

		if (ms == 0) {
			SPI_STATISTICS_INCREMENT_FIELD(statm, timedout);
			SPI_STATISTICS_INCREMENT_FIELD(stats, timedout);
			dev_err(&msg->spi->dev,
				"SPI transfer timed out\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}