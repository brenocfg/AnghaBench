#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct spi_message {int actual_length; } ;
struct fsl_dspi {int bytes_per_word; int /*<<< orphan*/  len; TYPE_1__* devtype_data; int /*<<< orphan*/  regmap; struct spi_message* cur_msg; } ;
typedef  enum dspi_trans_mode { ____Placeholder_dspi_trans_mode } dspi_trans_mode ;
struct TYPE_2__ {int trans_mode; } ;

/* Variables and functions */
 int DSPI_EOQ_MODE ; 
 int DSPI_TCFQ_MODE ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  SPI_TCR ; 
 int SPI_TCR_GET_TCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dspi_eoq_read (struct fsl_dspi*) ; 
 int /*<<< orphan*/  dspi_eoq_write (struct fsl_dspi*) ; 
 int /*<<< orphan*/  dspi_tcfq_read (struct fsl_dspi*) ; 
 int /*<<< orphan*/  dspi_tcfq_write (struct fsl_dspi*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dspi_rxtx(struct fsl_dspi *dspi)
{
	struct spi_message *msg = dspi->cur_msg;
	enum dspi_trans_mode trans_mode;
	u16 spi_tcnt;
	u32 spi_tcr;

	/* Get transfer counter (in number of SPI transfers). It was
	 * reset to 0 when transfer(s) were started.
	 */
	regmap_read(dspi->regmap, SPI_TCR, &spi_tcr);
	spi_tcnt = SPI_TCR_GET_TCNT(spi_tcr);
	/* Update total number of bytes that were transferred */
	msg->actual_length += spi_tcnt * dspi->bytes_per_word;

	trans_mode = dspi->devtype_data->trans_mode;
	if (trans_mode == DSPI_EOQ_MODE)
		dspi_eoq_read(dspi);
	else if (trans_mode == DSPI_TCFQ_MODE)
		dspi_tcfq_read(dspi);

	if (!dspi->len)
		/* Success! */
		return 0;

	if (trans_mode == DSPI_EOQ_MODE)
		dspi_eoq_write(dspi);
	else if (trans_mode == DSPI_TCFQ_MODE)
		dspi_tcfq_write(dspi);

	return -EINPROGRESS;
}