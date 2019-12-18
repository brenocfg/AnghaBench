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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct cr0014114 {size_t count; int do_recount; int /*<<< orphan*/  work; int /*<<< orphan*/ * dev; scalar_t__ delay; struct spi_device* spi; int /*<<< orphan*/  lock; void* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_FW_DELAY_MSEC ; 
 int /*<<< orphan*/  CR_RECOUNT_DELAY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cr0014114_probe_dt (struct cr0014114*) ; 
 int /*<<< orphan*/  cr0014114_recount_work ; 
 int cr0014114_sync (struct cr0014114*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 size_t device_get_child_node_count (int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  leds ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct cr0014114*) ; 
 size_t struct_size (struct cr0014114*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int cr0014114_probe(struct spi_device *spi)
{
	struct cr0014114	*priv;
	size_t			count;
	int			ret;

	count = device_get_child_node_count(&spi->dev);
	if (!count) {
		dev_err(&spi->dev, "LEDs are not defined in device tree!");
		return -ENODEV;
	}

	priv = devm_kzalloc(&spi->dev, struct_size(priv, leds, count),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->buf = devm_kzalloc(&spi->dev, count + 2, GFP_KERNEL);
	if (!priv->buf)
		return -ENOMEM;

	mutex_init(&priv->lock);
	INIT_DELAYED_WORK(&priv->work, cr0014114_recount_work);
	priv->count	= count;
	priv->dev	= &spi->dev;
	priv->spi	= spi;
	priv->delay	= jiffies -
			  msecs_to_jiffies(CR_FW_DELAY_MSEC);

	priv->do_recount = true;
	ret = cr0014114_sync(priv);
	if (ret) {
		dev_err(priv->dev, "first recount failed %d\n", ret);
		return ret;
	}

	priv->do_recount = true;
	ret = cr0014114_sync(priv);
	if (ret) {
		dev_err(priv->dev, "second recount failed %d\n", ret);
		return ret;
	}

	ret = cr0014114_probe_dt(priv);
	if (ret)
		return ret;

	/* setup recount work to workaround buggy firmware */
	schedule_delayed_work(&priv->work, CR_RECOUNT_DELAY);

	spi_set_drvdata(spi, priv);

	return 0;
}