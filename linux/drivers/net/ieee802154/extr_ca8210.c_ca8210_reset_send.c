#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct ca8210_platform_data* platform_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct ca8210_priv {int promiscuous; int /*<<< orphan*/  ca8210_is_awake; } ;
struct ca8210_platform_data {int /*<<< orphan*/  gpio_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA8210_SYNC_TIMEOUT ; 
 int /*<<< orphan*/  dev_crit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct ca8210_priv* spi_get_drvdata (struct spi_device*) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca8210_reset_send(struct spi_device *spi, unsigned int ms)
{
	struct ca8210_platform_data *pdata = spi->dev.platform_data;
	struct ca8210_priv *priv = spi_get_drvdata(spi);
	long status;

	gpio_set_value(pdata->gpio_reset, 0);
	reinit_completion(&priv->ca8210_is_awake);
	msleep(ms);
	gpio_set_value(pdata->gpio_reset, 1);
	priv->promiscuous = false;

	/* Wait until wakeup indication seen */
	status = wait_for_completion_interruptible_timeout(
		&priv->ca8210_is_awake,
		msecs_to_jiffies(CA8210_SYNC_TIMEOUT)
	);
	if (status == 0) {
		dev_crit(
			&spi->dev,
			"Fatal: No wakeup from ca8210 after reset!\n"
		);
	}

	dev_dbg(&spi->dev, "Reset the device\n");
}