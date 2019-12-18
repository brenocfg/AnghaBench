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
struct spi_message {struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/  statistics; struct spi_controller* controller; } ;
struct spi_controller {int (* transfer ) (struct spi_device*,struct spi_message*) ;int /*<<< orphan*/  statistics; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  SPI_STATISTICS_INCREMENT_FIELD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_async ; 
 int stub1 (struct spi_device*,struct spi_message*) ; 
 int /*<<< orphan*/  trace_spi_message_submit (struct spi_message*) ; 

__attribute__((used)) static int __spi_async(struct spi_device *spi, struct spi_message *message)
{
	struct spi_controller *ctlr = spi->controller;

	/*
	 * Some controllers do not support doing regular SPI transfers. Return
	 * ENOTSUPP when this is the case.
	 */
	if (!ctlr->transfer)
		return -ENOTSUPP;

	message->spi = spi;

	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics, spi_async);
	SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics, spi_async);

	trace_spi_message_submit(message);

	return ctlr->transfer(spi, message);
}