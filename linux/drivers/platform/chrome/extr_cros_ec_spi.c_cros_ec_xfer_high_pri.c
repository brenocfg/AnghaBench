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
struct cros_ec_xfer_work_params {int ret; int /*<<< orphan*/  work; int /*<<< orphan*/  fn; struct cros_ec_command* ec_msg; struct cros_ec_device* ec_dev; } ;
struct cros_ec_spi {int /*<<< orphan*/  high_pri_worker; } ;
struct cros_ec_device {struct cros_ec_spi* priv; } ;
struct cros_ec_command {int dummy; } ;
typedef  int /*<<< orphan*/  cros_ec_xfer_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  KTHREAD_WORK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cros_ec_xfer_high_pri_work ; 
 int /*<<< orphan*/  kthread_flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_xfer_high_pri(struct cros_ec_device *ec_dev,
				 struct cros_ec_command *ec_msg,
				 cros_ec_xfer_fn_t fn)
{
	struct cros_ec_spi *ec_spi = ec_dev->priv;
	struct cros_ec_xfer_work_params params = {
		.work = KTHREAD_WORK_INIT(params.work,
					  cros_ec_xfer_high_pri_work),
		.ec_dev = ec_dev,
		.ec_msg = ec_msg,
		.fn = fn,
	};

	/*
	 * This looks a bit ridiculous.  Why do the work on a
	 * different thread if we're just going to block waiting for
	 * the thread to finish?  The key here is that the thread is
	 * running at high priority but the calling context might not
	 * be.  We need to be at high priority to avoid getting
	 * context switched out for too long and the EC giving up on
	 * the transfer.
	 */
	kthread_queue_work(ec_spi->high_pri_worker, &params.work);
	kthread_flush_work(&params.work);

	return params.ret;
}