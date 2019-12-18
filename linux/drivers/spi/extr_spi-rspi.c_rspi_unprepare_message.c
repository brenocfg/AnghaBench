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
struct spi_message {int dummy; } ;
struct spi_controller {int dummy; } ;
struct rspi_data {int /*<<< orphan*/  spcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSPI_SPCMD0 ; 
 int /*<<< orphan*/  RSPI_SPCR ; 
 int /*<<< orphan*/  RSPI_SPSCR ; 
 int SPCR_SPE ; 
 int rspi_read8 (struct rspi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write16 (struct rspi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data*,int,int /*<<< orphan*/ ) ; 
 struct rspi_data* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int rspi_unprepare_message(struct spi_controller *ctlr,
				  struct spi_message *msg)
{
	struct rspi_data *rspi = spi_controller_get_devdata(ctlr);

	/* Disable SPI function */
	rspi_write8(rspi, rspi_read8(rspi, RSPI_SPCR) & ~SPCR_SPE, RSPI_SPCR);

	/* Reset sequencer for Single SPI Transfers */
	rspi_write16(rspi, rspi->spcmd, RSPI_SPCMD0);
	rspi_write8(rspi, 0, RSPI_SPSCR);
	return 0;
}