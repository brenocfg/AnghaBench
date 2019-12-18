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
struct spi_master {int dummy; } ;
struct rockchip_spi {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int RXDMA ; 
 int /*<<< orphan*/  TXDMA ; 
 int atomic_fetch_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  wait_for_idle (struct rockchip_spi*) ; 

__attribute__((used)) static void rockchip_spi_dma_txcb(void *data)
{
	struct spi_master *master = data;
	struct rockchip_spi *rs = spi_master_get_devdata(master);
	int state = atomic_fetch_andnot(TXDMA, &rs->state);

	if (state & RXDMA)
		return;

	/* Wait until the FIFO data completely. */
	wait_for_idle(rs);

	spi_enable_chip(rs, false);
	spi_finalize_current_transfer(master);
}