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
typedef  int u32 ;
struct spi_transfer {int bits_per_word; int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct adxrs450_state {int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  rx; TYPE_1__* us; int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADXRS450_CHK ; 
 int ADXRS450_P ; 
 int ADXRS450_SENSOR_DATA ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (TYPE_1__*,struct spi_transfer*,int) ; 

__attribute__((used)) static int adxrs450_spi_initial(struct adxrs450_state *st,
		u32 *val, char chk)
{
	int ret;
	u32 tx;
	struct spi_transfer xfers = {
		.tx_buf = &st->tx,
		.rx_buf = &st->rx,
		.bits_per_word = 8,
		.len = sizeof(st->tx),
	};

	mutex_lock(&st->buf_lock);
	tx = ADXRS450_SENSOR_DATA;
	if (chk)
		tx |= (ADXRS450_CHK | ADXRS450_P);
	st->tx = cpu_to_be32(tx);
	ret = spi_sync_transfer(st->us, &xfers, 1);
	if (ret) {
		dev_err(&st->us->dev, "Problem while reading initializing data\n");
		goto error_ret;
	}

	*val = be32_to_cpu(st->rx);

error_ret:
	mutex_unlock(&st->buf_lock);
	return ret;
}