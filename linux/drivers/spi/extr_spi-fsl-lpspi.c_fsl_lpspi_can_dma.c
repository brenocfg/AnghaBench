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
struct spi_transfer {int /*<<< orphan*/  bits_per_word; } ;
struct spi_device {int dummy; } ;
struct spi_controller {int /*<<< orphan*/  dma_rx; } ;

/* Variables and functions */
 unsigned int fsl_lpspi_bytes_per_word (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fsl_lpspi_can_dma(struct spi_controller *controller,
			      struct spi_device *spi,
			      struct spi_transfer *transfer)
{
	unsigned int bytes_per_word;

	if (!controller->dma_rx)
		return false;

	bytes_per_word = fsl_lpspi_bytes_per_word(transfer->bits_per_word);

	switch (bytes_per_word)
	{
		case 1:
		case 2:
		case 4:
			break;
		default:
			return false;
	}

	return true;
}