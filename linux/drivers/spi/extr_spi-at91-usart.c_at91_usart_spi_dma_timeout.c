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
struct at91_usart_spi {int /*<<< orphan*/  xfer_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  US_DMA_TIMEOUT ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long at91_usart_spi_dma_timeout(struct at91_usart_spi *aus)
{
	return wait_for_completion_timeout(&aus->xfer_completion,
					   US_DMA_TIMEOUT);
}