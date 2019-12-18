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
struct spi_qup {int /*<<< orphan*/  w_size; scalar_t__ rx_bytes; scalar_t__ tx_bytes; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ spi_qup_len (struct spi_qup*) ; 

__attribute__((used)) static bool spi_qup_data_pending(struct spi_qup *controller)
{
	unsigned int remainder_tx, remainder_rx;

	remainder_tx = DIV_ROUND_UP(spi_qup_len(controller) -
				    controller->tx_bytes, controller->w_size);

	remainder_rx = DIV_ROUND_UP(spi_qup_len(controller) -
				    controller->rx_bytes, controller->w_size);

	return remainder_tx || remainder_rx;
}