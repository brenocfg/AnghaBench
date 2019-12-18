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
struct spi_controller {int queued; int /*<<< orphan*/  dev; scalar_t__ transfer_one_message; int /*<<< orphan*/  transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spi_destroy_queue (struct spi_controller*) ; 
 int spi_init_queue (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_queued_transfer ; 
 int spi_start_queue (struct spi_controller*) ; 
 scalar_t__ spi_transfer_one_message ; 

__attribute__((used)) static int spi_controller_initialize_queue(struct spi_controller *ctlr)
{
	int ret;

	ctlr->transfer = spi_queued_transfer;
	if (!ctlr->transfer_one_message)
		ctlr->transfer_one_message = spi_transfer_one_message;

	/* Initialize and start queue */
	ret = spi_init_queue(ctlr);
	if (ret) {
		dev_err(&ctlr->dev, "problem initializing queue\n");
		goto err_init_queue;
	}
	ctlr->queued = true;
	ret = spi_start_queue(ctlr);
	if (ret) {
		dev_err(&ctlr->dev, "problem starting queue\n");
		goto err_start_queue;
	}

	return 0;

err_start_queue:
	spi_destroy_queue(ctlr);
err_init_queue:
	return ret;
}