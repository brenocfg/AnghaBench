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
struct pch_spi_data {int transfer_complete; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_dma_rx_complete(void *arg)
{
	struct pch_spi_data *data = arg;

	/* transfer is completed;inform pch_spi_process_messages_dma */
	data->transfer_complete = true;
	wake_up_interruptible(&data->wait);
}