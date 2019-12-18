#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {scalar_t__ manf_id; scalar_t__ card_id; int vpp; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; TYPE_3__** resource; int /*<<< orphan*/  config_flags; TYPE_2__* priv; } ;
struct ide_host {TYPE_1__** ports; } ;
struct TYPE_5__ {int ndev; struct ide_host* host; } ;
typedef  TYPE_2__ ide_info_t ;
struct TYPE_6__ {unsigned long start; scalar_t__ end; } ;
struct TYPE_4__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_AUTO_CHECK_VCC ; 
 int ENODEV ; 
 scalar_t__ MANFID_KME ; 
 scalar_t__ PRODID_KME_KXLC005_A ; 
 scalar_t__ PRODID_KME_KXLC005_B ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char,int,int) ; 
 int /*<<< orphan*/  ide_release (struct pcmcia_device*) ; 
 struct ide_host* idecs_register (unsigned long,unsigned long,int /*<<< orphan*/ ,struct pcmcia_device*) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  pcmcia_check_one_config ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int*) ; 
 int resource_size (TYPE_3__*) ; 

__attribute__((used)) static int ide_config(struct pcmcia_device *link)
{
    ide_info_t *info = link->priv;
    int ret = 0, is_kme = 0;
    unsigned long io_base, ctl_base;
    struct ide_host *host;

    dev_dbg(&link->dev, "ide_config(0x%p)\n", link);

    is_kme = ((link->manf_id == MANFID_KME) &&
	      ((link->card_id == PRODID_KME_KXLC005_A) ||
	       (link->card_id == PRODID_KME_KXLC005_B)));

    if (pcmcia_loop_config(link, pcmcia_check_one_config, &is_kme)) {
	    link->config_flags &= ~CONF_AUTO_CHECK_VCC;
	    if (pcmcia_loop_config(link, pcmcia_check_one_config, &is_kme))
		    goto failed; /* No suitable config found */
    }
    io_base = link->resource[0]->start;
    if (link->resource[1]->end)
	    ctl_base = link->resource[1]->start;
    else
	    ctl_base = link->resource[0]->start + 0x0e;

    if (!link->irq)
	    goto failed;

    ret = pcmcia_enable_device(link);
    if (ret)
	    goto failed;

    /* disable drive interrupts during IDE probe */
    outb(0x02, ctl_base);

    /* special setup for KXLC005 card */
    if (is_kme)
	outb(0x81, ctl_base+1);

     host = idecs_register(io_base, ctl_base, link->irq, link);
     if (host == NULL && resource_size(link->resource[0]) == 0x20) {
	    outb(0x02, ctl_base + 0x10);
	    host = idecs_register(io_base + 0x10, ctl_base + 0x10,
				  link->irq, link);
    }

    if (host == NULL)
	goto failed;

    info->ndev = 1;
    info->host = host;
    dev_info(&link->dev, "ide-cs: hd%c: Vpp = %d.%d\n",
	    'a' + host->ports[0]->index * 2,
	    link->vpp / 10, link->vpp % 10);

    return 0;

failed:
    ide_release(link);
    return -ENODEV;
}