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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sirfsoc_spi {int /*<<< orphan*/  left_tx_word; TYPE_1__* regs; scalar_t__ base; int /*<<< orphan*/  const* tx; } ;
struct TYPE_2__ {scalar_t__ txfifo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void spi_sirfsoc_tx_word_u8(struct sirfsoc_spi *sspi)
{
	u32 data = 0;
	const u8 *tx = sspi->tx;

	if (tx) {
		data = *tx++;
		sspi->tx = tx;
	}
	writel(data, sspi->base + sspi->regs->txfifo_data);
	sspi->left_tx_word--;
}