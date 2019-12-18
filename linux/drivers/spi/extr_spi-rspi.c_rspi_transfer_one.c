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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {scalar_t__ rx_buf; } ;
struct spi_device {int dummy; } ;
struct spi_controller {int dummy; } ;
struct rspi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSPI_SPCR ; 
 int /*<<< orphan*/  SPCR_TXMD ; 
 int rspi_common_transfer (struct rspi_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  rspi_read8 (struct rspi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_receive_init (struct rspi_data*) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rspi_data* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int rspi_transfer_one(struct spi_controller *ctlr,
			     struct spi_device *spi, struct spi_transfer *xfer)
{
	struct rspi_data *rspi = spi_controller_get_devdata(ctlr);
	u8 spcr;

	spcr = rspi_read8(rspi, RSPI_SPCR);
	if (xfer->rx_buf) {
		rspi_receive_init(rspi);
		spcr &= ~SPCR_TXMD;
	} else {
		spcr |= SPCR_TXMD;
	}
	rspi_write8(rspi, spcr, RSPI_SPCR);

	return rspi_common_transfer(rspi, xfer);
}