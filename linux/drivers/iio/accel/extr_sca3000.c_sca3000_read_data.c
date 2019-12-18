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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct sca3000_state {TYPE_1__* us; int /*<<< orphan*/ * tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int /*<<< orphan*/  SCA3000_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (TYPE_1__*,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sca3000_read_data(struct sca3000_state *st,
			     u8 reg_address_high,
			     u8 *rx,
			     int len)
{
	int ret;
	struct spi_transfer xfer[2] = {
		{
			.len = 1,
			.tx_buf = st->tx,
		}, {
			.len = len,
			.rx_buf = rx,
		}
	};

	st->tx[0] = SCA3000_READ_REG(reg_address_high);
	ret = spi_sync_transfer(st->us, xfer, ARRAY_SIZE(xfer));
	if (ret) {
		dev_err(get_device(&st->us->dev), "problem reading register");
		return ret;
	}

	return 0;
}