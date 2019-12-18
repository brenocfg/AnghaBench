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
struct TYPE_4__ {struct spi_slave_system_control_priv* context; int /*<<< orphan*/  complete; } ;
struct spi_slave_system_control_priv {TYPE_2__* spi; TYPE_1__ msg; int /*<<< orphan*/  xfer; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_async (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_slave_system_control_complete ; 

__attribute__((used)) static
int spi_slave_system_control_submit(struct spi_slave_system_control_priv *priv)
{
	int ret;

	spi_message_init_with_transfers(&priv->msg, &priv->xfer, 1);

	priv->msg.complete = spi_slave_system_control_complete;
	priv->msg.context = priv;

	ret = spi_async(priv->spi, &priv->msg);
	if (ret)
		dev_err(&priv->spi->dev, "spi_async() failed %d\n", ret);

	return ret;
}