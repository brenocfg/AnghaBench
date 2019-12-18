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
struct spi_transfer {int len; int* rx_buf; unsigned char* tx_buf; } ;
struct ad2s1210_state {int* rx; unsigned char* tx; int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 unsigned char AD2S1210_MSB_IS_HIGH ; 
 unsigned char AD2S1210_REG_FAULT ; 
 int /*<<< orphan*/  MOD_CONFIG ; 
 int /*<<< orphan*/  ad2s1210_set_mode (int /*<<< orphan*/ ,struct ad2s1210_state*) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int) ; 

__attribute__((used)) static int ad2s1210_config_read(struct ad2s1210_state *st,
				unsigned char address)
{
	struct spi_transfer xfer = {
		.len = 2,
		.rx_buf = st->rx,
		.tx_buf = st->tx,
	};
	int ret = 0;

	ad2s1210_set_mode(MOD_CONFIG, st);
	st->tx[0] = address | AD2S1210_MSB_IS_HIGH;
	st->tx[1] = AD2S1210_REG_FAULT;
	ret = spi_sync_transfer(st->sdev, &xfer, 1);
	if (ret < 0)
		return ret;

	return st->rx[1];
}