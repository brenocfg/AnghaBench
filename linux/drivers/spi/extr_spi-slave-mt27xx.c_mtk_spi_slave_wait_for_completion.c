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
struct mtk_spi_slave {int /*<<< orphan*/  dev; scalar_t__ slave_aborted; int /*<<< orphan*/  xfer_done; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_spi_slave_wait_for_completion(struct mtk_spi_slave *mdata)
{
	if (wait_for_completion_interruptible(&mdata->xfer_done) ||
	    mdata->slave_aborted) {
		dev_err(mdata->dev, "interrupted\n");
		return -EINTR;
	}

	return 0;
}