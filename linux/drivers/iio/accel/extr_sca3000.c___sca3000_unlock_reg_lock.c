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
struct spi_transfer {int len; int cs_change; int* tx_buf; } ;
struct sca3000_state {int* tx; int /*<<< orphan*/  us; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int /*<<< orphan*/  SCA3000_REG_UNLOCK_ADDR ; 
 void* SCA3000_WRITE_REG (int /*<<< orphan*/ ) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __sca3000_unlock_reg_lock(struct sca3000_state *st)
{
	struct spi_transfer xfer[3] = {
		{
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx,
		}, {
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx + 2,
		}, {
			.len = 2,
			.tx_buf = st->tx + 4,
		},
	};
	st->tx[0] = SCA3000_WRITE_REG(SCA3000_REG_UNLOCK_ADDR);
	st->tx[1] = 0x00;
	st->tx[2] = SCA3000_WRITE_REG(SCA3000_REG_UNLOCK_ADDR);
	st->tx[3] = 0x50;
	st->tx[4] = SCA3000_WRITE_REG(SCA3000_REG_UNLOCK_ADDR);
	st->tx[5] = 0xA0;

	return spi_sync_transfer(st->us, xfer, ARRAY_SIZE(xfer));
}