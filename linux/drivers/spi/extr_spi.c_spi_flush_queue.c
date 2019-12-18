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
struct spi_controller {scalar_t__ transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __spi_pump_messages (struct spi_controller*,int) ; 
 scalar_t__ spi_queued_transfer ; 

void spi_flush_queue(struct spi_controller *ctlr)
{
	if (ctlr->transfer == spi_queued_transfer)
		__spi_pump_messages(ctlr, false);
}