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
typedef  int u32 ;
struct spi_transfer {scalar_t__ len; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct scratch {int* status; int /*<<< orphan*/  crc_val; } ;
struct mmc_spi_host {scalar_t__ dma_dev; int /*<<< orphan*/  data_dma; int /*<<< orphan*/  m; TYPE_1__* mmc; struct scratch* data; struct spi_device* spi; } ;
struct TYPE_2__ {scalar_t__ use_spi_crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EILSEQ ; 
 int EIO ; 
 int EPROTO ; 
#define  SPI_RESPONSE_ACCEPTED 130 
#define  SPI_RESPONSE_CRC_ERR 129 
#define  SPI_RESPONSE_WRITE_ERR 128 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_itu_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int get_unaligned_be32 (int*) ; 
 int mmc_spi_wait_unbusy (struct mmc_spi_host*,unsigned long) ; 
 int spi_sync_locked (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mmc_spi_writeblock(struct mmc_spi_host *host, struct spi_transfer *t,
	unsigned long timeout)
{
	struct spi_device	*spi = host->spi;
	int			status, i;
	struct scratch		*scratch = host->data;
	u32			pattern;

	if (host->mmc->use_spi_crc)
		scratch->crc_val = cpu_to_be16(crc_itu_t(0, t->tx_buf, t->len));
	if (host->dma_dev)
		dma_sync_single_for_device(host->dma_dev,
				host->data_dma, sizeof(*scratch),
				DMA_BIDIRECTIONAL);

	status = spi_sync_locked(spi, &host->m);

	if (status != 0) {
		dev_dbg(&spi->dev, "write error (%d)\n", status);
		return status;
	}

	if (host->dma_dev)
		dma_sync_single_for_cpu(host->dma_dev,
				host->data_dma, sizeof(*scratch),
				DMA_BIDIRECTIONAL);

	/*
	 * Get the transmission data-response reply.  It must follow
	 * immediately after the data block we transferred.  This reply
	 * doesn't necessarily tell whether the write operation succeeded;
	 * it just says if the transmission was ok and whether *earlier*
	 * writes succeeded; see the standard.
	 *
	 * In practice, there are (even modern SDHC-)cards which are late
	 * in sending the response, and miss the time frame by a few bits,
	 * so we have to cope with this situation and check the response
	 * bit-by-bit. Arggh!!!
	 */
	pattern = get_unaligned_be32(scratch->status);

	/* First 3 bit of pattern are undefined */
	pattern |= 0xE0000000;

	/* left-adjust to leading 0 bit */
	while (pattern & 0x80000000)
		pattern <<= 1;
	/* right-adjust for pattern matching. Code is in bit 4..0 now. */
	pattern >>= 27;

	switch (pattern) {
	case SPI_RESPONSE_ACCEPTED:
		status = 0;
		break;
	case SPI_RESPONSE_CRC_ERR:
		/* host shall then issue MMC_STOP_TRANSMISSION */
		status = -EILSEQ;
		break;
	case SPI_RESPONSE_WRITE_ERR:
		/* host shall then issue MMC_STOP_TRANSMISSION,
		 * and should MMC_SEND_STATUS to sort it out
		 */
		status = -EIO;
		break;
	default:
		status = -EPROTO;
		break;
	}
	if (status != 0) {
		dev_dbg(&spi->dev, "write error %02x (%d)\n",
			scratch->status[0], status);
		return status;
	}

	t->tx_buf += t->len;
	if (host->dma_dev)
		t->tx_dma += t->len;

	/* Return when not busy.  If we didn't collect that status yet,
	 * we'll need some more I/O.
	 */
	for (i = 4; i < sizeof(scratch->status); i++) {
		/* card is non-busy if the most recent bit is 1 */
		if (scratch->status[i] & 0x01)
			return 0;
	}
	return mmc_spi_wait_unbusy(host, timeout);
}