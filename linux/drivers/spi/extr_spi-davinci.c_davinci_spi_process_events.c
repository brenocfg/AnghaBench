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
typedef  int u32 ;
struct davinci_spi {scalar_t__ rcount; scalar_t__ wcount; int (* get_tx ) (struct davinci_spi*) ;scalar_t__ base; int /*<<< orphan*/  (* get_rx ) (int,struct davinci_spi*) ;} ;

/* Variables and functions */
 scalar_t__ SPIBUF ; 
 int SPIBUF_RXEMPTY_MASK ; 
 int SPIBUF_TXFULL_MASK ; 
 scalar_t__ SPIDAT1 ; 
 scalar_t__ SPIFLG ; 
 int SPIFLG_ERROR_MASK ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int,struct davinci_spi*) ; 
 int stub2 (struct davinci_spi*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int davinci_spi_process_events(struct davinci_spi *dspi)
{
	u32 buf, status, errors = 0, spidat1;

	buf = ioread32(dspi->base + SPIBUF);

	if (dspi->rcount > 0 && !(buf & SPIBUF_RXEMPTY_MASK)) {
		dspi->get_rx(buf & 0xFFFF, dspi);
		dspi->rcount--;
	}

	status = ioread32(dspi->base + SPIFLG);

	if (unlikely(status & SPIFLG_ERROR_MASK)) {
		errors = status & SPIFLG_ERROR_MASK;
		goto out;
	}

	if (dspi->wcount > 0 && !(buf & SPIBUF_TXFULL_MASK)) {
		spidat1 = ioread32(dspi->base + SPIDAT1);
		dspi->wcount--;
		spidat1 &= ~0xFFFF;
		spidat1 |= 0xFFFF & dspi->get_tx(dspi);
		iowrite32(spidat1, dspi->base + SPIDAT1);
	}

out:
	return errors;
}