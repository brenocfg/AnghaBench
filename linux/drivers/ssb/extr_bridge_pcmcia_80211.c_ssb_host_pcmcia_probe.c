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
struct ssb_bus {int dummy; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; struct ssb_bus* priv; TYPE_1__** resource; int /*<<< orphan*/  irq; int /*<<< orphan*/  config_flags; } ;
struct TYPE_3__ {int flags; scalar_t__ start; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SSB_CORE_SIZE ; 
 int WIN_DATA_WIDTH_16 ; 
 int WIN_ENABLE ; 
 int WIN_USE_WAIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct ssb_bus*) ; 
 struct ssb_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_map_mem_page (struct pcmcia_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pcmcia_request_window (struct pcmcia_device*,TYPE_1__*,int) ; 
 int ssb_bus_pcmciabus_register (struct ssb_bus*,struct pcmcia_device*,scalar_t__) ; 

__attribute__((used)) static int ssb_host_pcmcia_probe(struct pcmcia_device *dev)
{
	struct ssb_bus *ssb;
	int err = -ENOMEM;
	int res = 0;

	ssb = kzalloc(sizeof(*ssb), GFP_KERNEL);
	if (!ssb)
		goto out_error;

	err = -ENODEV;

	dev->config_flags |= CONF_ENABLE_IRQ;

	dev->resource[2]->flags |=  WIN_ENABLE | WIN_DATA_WIDTH_16 |
			 WIN_USE_WAIT;
	dev->resource[2]->start = 0;
	dev->resource[2]->end = SSB_CORE_SIZE;
	res = pcmcia_request_window(dev, dev->resource[2], 250);
	if (res != 0)
		goto err_kfree_ssb;

	res = pcmcia_map_mem_page(dev, dev->resource[2], 0);
	if (res != 0)
		goto err_disable;

	if (!dev->irq)
		goto err_disable;

	res = pcmcia_enable_device(dev);
	if (res != 0)
		goto err_disable;

	err = ssb_bus_pcmciabus_register(ssb, dev, dev->resource[2]->start);
	if (err)
		goto err_disable;
	dev->priv = ssb;

	return 0;

err_disable:
	pcmcia_disable_device(dev);
err_kfree_ssb:
	kfree(ssb);
out_error:
	dev_err(&dev->dev, "Initialization failed (%d, %d)\n", res, err);
	return err;
}