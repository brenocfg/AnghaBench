#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct serial_info {int multi; scalar_t__ ndev; TYPE_2__* quirk; int /*<<< orphan*/  prodid; int /*<<< orphan*/  manfid; } ;
struct pcmcia_device {scalar_t__ func_id; int /*<<< orphan*/  dev; TYPE_1__* socket; int /*<<< orphan*/  card_id; int /*<<< orphan*/  manf_id; scalar_t__ has_func_id; struct serial_info* priv; } ;
struct TYPE_6__ {int multi; scalar_t__ (* post ) (struct pcmcia_device*) ;int /*<<< orphan*/  prodid; int /*<<< orphan*/  manfid; } ;
struct TYPE_5__ {int functions; scalar_t__ pcmcia_pfc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ CISTPL_FUNCID_MULTI ; 
 scalar_t__ CISTPL_FUNCID_SERIAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int multi_config (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,struct serial_info*) ; 
 int pfc_config (struct pcmcia_device*) ; 
 TYPE_2__* quirks ; 
 int /*<<< orphan*/  serial_check_for_multi ; 
 int /*<<< orphan*/  serial_remove (struct pcmcia_device*) ; 
 int simple_config (struct pcmcia_device*) ; 
 scalar_t__ stub1 (struct pcmcia_device*) ; 

__attribute__((used)) static int serial_config(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;
	int i;

	dev_dbg(&link->dev, "serial_config\n");

	/* Is this a compliant multifunction card? */
	info->multi = (link->socket->functions > 1);

	/* Is this a multiport card? */
	info->manfid = link->manf_id;
	info->prodid = link->card_id;

	for (i = 0; i < ARRAY_SIZE(quirks); i++)
		if ((quirks[i].manfid == ~0 ||
		     quirks[i].manfid == info->manfid) &&
		    (quirks[i].prodid == ~0 ||
		     quirks[i].prodid == info->prodid)) {
			info->quirk = &quirks[i];
			break;
		}

	/*
	 * Another check for dual-serial cards: look for either serial or
	 * multifunction cards that ask for appropriate IO port ranges.
	 */
	if ((info->multi == 0) &&
	    (link->has_func_id) &&
	    (link->socket->pcmcia_pfc == 0) &&
	    ((link->func_id == CISTPL_FUNCID_MULTI) ||
	     (link->func_id == CISTPL_FUNCID_SERIAL))) {
		if (pcmcia_loop_config(link, serial_check_for_multi, info))
			goto failed;
	}

	/*
	 * Apply any multi-port quirk.
	 */
	if (info->quirk && info->quirk->multi != -1)
		info->multi = info->quirk->multi;

	dev_info(&link->dev,
		"trying to set up [0x%04x:0x%04x] (pfc: %d, multi: %d, quirk: %p)\n",
		link->manf_id, link->card_id,
		link->socket->pcmcia_pfc, info->multi, info->quirk);
	if (link->socket->pcmcia_pfc)
		i = pfc_config(link);
	else if (info->multi > 1)
		i = multi_config(link);
	else
		i = simple_config(link);

	if (i || info->ndev == 0)
		goto failed;

	/*
	 * Apply any post-init quirk.  FIXME: This should really happen
	 * before we register the port, since it might already be in use.
	 */
	if (info->quirk && info->quirk->post)
		if (info->quirk->post(link))
			goto failed;

	return 0;

failed:
	dev_warn(&link->dev, "failed to initialize\n");
	serial_remove(link);
	return -ENODEV;
}