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
struct spi_controller {int dummy; } ;
struct fsl_lpspi_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  xfer_done; scalar_t__ slave_aborted; scalar_t__ is_slave; } ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct fsl_lpspi_data* spi_controller_get_devdata (struct spi_controller*) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_lpspi_wait_for_completion(struct spi_controller *controller)
{
	struct fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	if (fsl_lpspi->is_slave) {
		if (wait_for_completion_interruptible(&fsl_lpspi->xfer_done) ||
			fsl_lpspi->slave_aborted) {
			dev_dbg(fsl_lpspi->dev, "interrupted\n");
			return -EINTR;
		}
	} else {
		if (!wait_for_completion_timeout(&fsl_lpspi->xfer_done, HZ)) {
			dev_dbg(fsl_lpspi->dev, "wait for completion timeout\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}