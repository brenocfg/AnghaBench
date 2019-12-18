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
struct spi_message {scalar_t__ frame_length; scalar_t__ actual_length; } ;
struct spi_test {int /*<<< orphan*/  elapsed_time; struct spi_message msg; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int dump_messages ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  simulate_only ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 int spi_test_check_elapsed_time (struct spi_device*,struct spi_test*) ; 
 int spi_test_check_loopback_result (struct spi_device*,struct spi_message*,void*,void*) ; 
 int /*<<< orphan*/  spi_test_dump_message (struct spi_device*,struct spi_message*,int) ; 

int spi_test_execute_msg(struct spi_device *spi, struct spi_test *test,
			 void *tx, void *rx)
{
	struct spi_message *msg = &test->msg;
	int ret = 0;
	int i;

	/* only if we do not simulate */
	if (!simulate_only) {
		ktime_t start;

		/* dump the complete message before and after the transfer */
		if (dump_messages == 3)
			spi_test_dump_message(spi, msg, true);

		start = ktime_get();
		/* run spi message */
		ret = spi_sync(spi, msg);
		test->elapsed_time = ktime_to_ns(ktime_sub(ktime_get(), start));
		if (ret == -ETIMEDOUT) {
			dev_info(&spi->dev,
				 "spi-message timed out - rerunning...\n");
			/* rerun after a few explicit schedules */
			for (i = 0; i < 16; i++)
				schedule();
			ret = spi_sync(spi, msg);
		}
		if (ret) {
			dev_err(&spi->dev,
				"Failed to execute spi_message: %i\n",
				ret);
			goto exit;
		}

		/* do some extra error checks */
		if (msg->frame_length != msg->actual_length) {
			dev_err(&spi->dev,
				"actual length differs from expected\n");
			ret = -EIO;
			goto exit;
		}

		/* run rx-buffer tests */
		ret = spi_test_check_loopback_result(spi, msg, tx, rx);
		if (ret)
			goto exit;

		ret = spi_test_check_elapsed_time(spi, test);
	}

	/* if requested or on error dump message (including data) */
exit:
	if (dump_messages || ret)
		spi_test_dump_message(spi, msg,
				      (dump_messages >= 2) || (ret));

	return ret;
}