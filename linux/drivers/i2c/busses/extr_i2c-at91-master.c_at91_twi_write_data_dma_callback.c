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
struct at91_twi_dev {int /*<<< orphan*/  use_alt_cmd; int /*<<< orphan*/  buf_len; TYPE_1__ dma; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_CR ; 
 int /*<<< orphan*/  AT91_TWI_IER ; 
 int /*<<< orphan*/  AT91_TWI_STOP ; 
 int /*<<< orphan*/  AT91_TWI_TXCOMP ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void at91_twi_write_data_dma_callback(void *data)
{
	struct at91_twi_dev *dev = (struct at91_twi_dev *)data;

	dma_unmap_single(dev->dev, sg_dma_address(&dev->dma.sg[0]),
			 dev->buf_len, DMA_TO_DEVICE);

	/*
	 * When this callback is called, THR/TX FIFO is likely not to be empty
	 * yet. So we have to wait for TXCOMP or NACK bits to be set into the
	 * Status Register to be sure that the STOP bit has been sent and the
	 * transfer is completed. The NACK interrupt has already been enabled,
	 * we just have to enable TXCOMP one.
	 */
	at91_twi_write(dev, AT91_TWI_IER, AT91_TWI_TXCOMP);
	if (!dev->use_alt_cmd)
		at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_STOP);
}