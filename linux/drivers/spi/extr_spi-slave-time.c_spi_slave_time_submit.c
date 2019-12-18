#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {struct spi_slave_time_priv* context; int /*<<< orphan*/  complete; } ;
struct spi_slave_time_priv {TYPE_2__* spi; TYPE_1__ msg; int /*<<< orphan*/  xfer; void** buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int do_div (int,int) ; 
 int local_clock () ; 
 int spi_async (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_slave_time_complete ; 

__attribute__((used)) static int spi_slave_time_submit(struct spi_slave_time_priv *priv)
{
	u32 rem_us;
	int ret;
	u64 ts;

	ts = local_clock();
	rem_us = do_div(ts, 1000000000) / 1000;

	priv->buf[0] = cpu_to_be32(ts);
	priv->buf[1] = cpu_to_be32(rem_us);

	spi_message_init_with_transfers(&priv->msg, &priv->xfer, 1);

	priv->msg.complete = spi_slave_time_complete;
	priv->msg.context = priv;

	ret = spi_async(priv->spi, &priv->msg);
	if (ret)
		dev_err(&priv->spi->dev, "spi_async() failed %d\n", ret);

	return ret;
}