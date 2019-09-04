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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct sca3000_state {int /*<<< orphan*/  us; int /*<<< orphan*/ * tx; int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int /*<<< orphan*/  SCA3000_READ_REG (int /*<<< orphan*/ ) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sca3000_read_data_short(struct sca3000_state *st,
				   u8 reg_address_high,
				   int len)
{
	struct spi_transfer xfer[2] = {
		{
			.len = 1,
			.tx_buf = st->tx,
		}, {
			.len = len,
			.rx_buf = st->rx,
		}
	};
	st->tx[0] = SCA3000_READ_REG(reg_address_high);

	return spi_sync_transfer(st->us, xfer, ARRAY_SIZE(xfer));
}