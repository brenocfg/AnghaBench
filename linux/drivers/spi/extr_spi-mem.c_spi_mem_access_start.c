#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_mem {TYPE_1__* spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct spi_controller {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  bus_lock_mutex; TYPE_2__ dev; scalar_t__ auto_runtime_pm; } ;
struct TYPE_3__ {struct spi_controller* controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_flush_queue (struct spi_controller*) ; 

__attribute__((used)) static int spi_mem_access_start(struct spi_mem *mem)
{
	struct spi_controller *ctlr = mem->spi->controller;

	/*
	 * Flush the message queue before executing our SPI memory
	 * operation to prevent preemption of regular SPI transfers.
	 */
	spi_flush_queue(ctlr);

	if (ctlr->auto_runtime_pm) {
		int ret;

		ret = pm_runtime_get_sync(ctlr->dev.parent);
		if (ret < 0) {
			dev_err(&ctlr->dev, "Failed to power device: %d\n",
				ret);
			return ret;
		}
	}

	mutex_lock(&ctlr->bus_lock_mutex);
	mutex_lock(&ctlr->io_mutex);

	return 0;
}