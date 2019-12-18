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
struct TYPE_2__ {int /*<<< orphan*/ * sg; } ;
struct at91_twi_dev {int buf_len; int /*<<< orphan*/  buf; int /*<<< orphan*/  use_alt_cmd; TYPE_1__ dma; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_IER ; 
 unsigned int AT91_TWI_RXRDY ; 
 unsigned int AT91_TWI_TXCOMP ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void at91_twi_read_data_dma_callback(void *data)
{
	struct at91_twi_dev *dev = (struct at91_twi_dev *)data;
	unsigned ier = AT91_TWI_TXCOMP;

	dma_unmap_single(dev->dev, sg_dma_address(&dev->dma.sg[0]),
			 dev->buf_len, DMA_FROM_DEVICE);

	if (!dev->use_alt_cmd) {
		/* The last two bytes have to be read without using dma */
		dev->buf += dev->buf_len - 2;
		dev->buf_len = 2;
		ier |= AT91_TWI_RXRDY;
	}
	at91_twi_write(dev, AT91_TWI_IER, ier);
}