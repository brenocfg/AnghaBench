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
typedef  unsigned int u32 ;
struct spi_device {unsigned int* controller_state; int mode; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  controller; } ;
struct at91_usart_spi {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MR ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 unsigned int US_MR_CPHA ; 
 unsigned int US_MR_CPOL ; 
 unsigned int US_MR_LOOP ; 
 unsigned int at91_usart_spi_readl (struct at91_usart_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct at91_usart_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_usart_spi_setup(struct spi_device *spi)
{
	struct at91_usart_spi *aus = spi_master_get_devdata(spi->controller);
	u32 *ausd = spi->controller_state;
	unsigned int mr = at91_usart_spi_readl(aus, MR);

	if (spi->mode & SPI_CPOL)
		mr |= US_MR_CPOL;
	else
		mr &= ~US_MR_CPOL;

	if (spi->mode & SPI_CPHA)
		mr |= US_MR_CPHA;
	else
		mr &= ~US_MR_CPHA;

	if (spi->mode & SPI_LOOP)
		mr |= US_MR_LOOP;
	else
		mr &= ~US_MR_LOOP;

	if (!ausd) {
		ausd = kzalloc(sizeof(*ausd), GFP_KERNEL);
		if (!ausd)
			return -ENOMEM;

		spi->controller_state = ausd;
	}

	*ausd = mr;

	dev_dbg(&spi->dev,
		"setup: bpw %u mode 0x%x -> mr %d %08x\n",
		spi->bits_per_word, spi->mode, spi->chip_select, mr);

	return 0;
}