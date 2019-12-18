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
struct pcmcia_device {int config_flags; scalar_t__ priv; int /*<<< orphan*/  dev; TYPE_1__** resource; int /*<<< orphan*/  irq; } ;
struct local_info {int /*<<< orphan*/  eth_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONF_AUTO_AUDIO ; 
 int CONF_AUTO_SET_IO ; 
 int CONF_AUTO_SET_VPP ; 
 int CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 int /*<<< orphan*/  airo_cs_config_check ; 
 int /*<<< orphan*/  airo_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_airo_card (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int airo_config(struct pcmcia_device *link)
{
	int ret;

	dev_dbg(&link->dev, "airo_config\n");

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
		CONF_AUTO_AUDIO | CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, airo_cs_config_check, NULL);
	if (ret)
		goto failed;

	if (!link->irq)
		goto failed;

	ret = pcmcia_enable_device(link);
	if (ret)
		goto failed;
	((struct local_info *)link->priv)->eth_dev =
		init_airo_card(link->irq,
			       link->resource[0]->start, 1, &link->dev);
	if (!((struct local_info *)link->priv)->eth_dev)
		goto failed;

	return 0;

 failed:
	airo_release(link);
	return -ENODEV;
}