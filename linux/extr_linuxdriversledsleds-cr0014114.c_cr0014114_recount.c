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
struct cr0014114 {size_t count; int /*<<< orphan*/  dev; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CR_FW_DELAY_MSEC ; 
 int /*<<< orphan*/  CR_INIT_REENUMERATE ; 
 int /*<<< orphan*/  CR_NEXT_REENUMERATE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cr0014114_recount(struct cr0014114 *priv)
{
	int	ret;
	size_t	i;
	u8	cmd;

	dev_dbg(priv->dev, "LEDs recount is started\n");

	cmd = CR_INIT_REENUMERATE;
	ret = spi_write(priv->spi, &cmd, sizeof(cmd));
	if (ret)
		goto err;

	cmd = CR_NEXT_REENUMERATE;
	for (i = 0; i < priv->count; i++) {
		msleep(CR_FW_DELAY_MSEC);

		ret = spi_write(priv->spi, &cmd, sizeof(cmd));
		if (ret)
			goto err;
	}

err:
	dev_dbg(priv->dev, "LEDs recount is finished\n");

	if (ret)
		dev_err(priv->dev, "with error %d", ret);

	return ret;
}