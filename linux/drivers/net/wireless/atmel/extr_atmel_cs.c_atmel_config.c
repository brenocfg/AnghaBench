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
struct pcmcia_device_id {int /*<<< orphan*/  driver_info; } ;
struct pcmcia_device {int config_flags; struct local_info* priv; int /*<<< orphan*/  dev; TYPE_1__** resource; int /*<<< orphan*/  irq; } ;
struct local_info {int /*<<< orphan*/  eth_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_FW_TYPE_NONE ; 
 int CONF_AUTO_AUDIO ; 
 int CONF_AUTO_SET_IO ; 
 int CONF_AUTO_SET_VPP ; 
 int CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 int /*<<< orphan*/  atmel_config_check ; 
 int /*<<< orphan*/  atmel_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  card_present ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pcmcia_device_id* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_atmel_card (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_config(struct pcmcia_device *link)
{
	struct local_info *dev;
	int ret;
	const struct pcmcia_device_id *did;

	dev = link->priv;
	did = dev_get_drvdata(&link->dev);

	dev_dbg(&link->dev, "atmel_config\n");

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
		CONF_AUTO_AUDIO | CONF_AUTO_SET_IO;

	if (pcmcia_loop_config(link, atmel_config_check, NULL))
		goto failed;

	if (!link->irq) {
		dev_err(&link->dev, "atmel: cannot assign IRQ: check that CONFIG_ISA is set in kernel config.");
		goto failed;
	}

	ret = pcmcia_enable_device(link);
	if (ret)
		goto failed;

	((struct local_info *)link->priv)->eth_dev =
		init_atmel_card(link->irq,
				link->resource[0]->start,
				did ? did->driver_info : ATMEL_FW_TYPE_NONE,
				&link->dev,
				card_present,
				link);
	if (!((struct local_info *)link->priv)->eth_dev)
			goto failed;


	return 0;

 failed:
	atmel_release(link);
	return -ENODEV;
}