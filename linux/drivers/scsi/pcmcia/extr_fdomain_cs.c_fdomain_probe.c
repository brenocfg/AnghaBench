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
struct pcmcia_device {int config_flags; TYPE_1__** resource; struct Scsi_Host* priv; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  config_regs; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 int /*<<< orphan*/  FDOMAIN_REGION_SIZE ; 
 int /*<<< orphan*/  PRESENT_OPTION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fdomain_config_check ; 
 struct Scsi_Host* fdomain_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fdomain_probe(struct pcmcia_device *link)
{
	int ret;
	struct Scsi_Host *sh;

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
	link->config_regs = PRESENT_OPTION;

	ret = pcmcia_loop_config(link, fdomain_config_check, NULL);
	if (ret)
		return ret;

	ret = pcmcia_enable_device(link);
	if (ret)
		goto fail_disable;

	if (!request_region(link->resource[0]->start, FDOMAIN_REGION_SIZE,
			    "fdomain_cs"))
		goto fail_disable;

	sh = fdomain_create(link->resource[0]->start, link->irq, 7, &link->dev);
	if (!sh) {
		dev_err(&link->dev, "Controller initialization failed");
		ret = -ENODEV;
		goto fail_release;
	}

	link->priv = sh;

	return 0;

fail_release:
	release_region(link->resource[0]->start, FDOMAIN_REGION_SIZE);
fail_disable:
	pcmcia_disable_device(link);
	return ret;
}