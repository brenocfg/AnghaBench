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
struct pcmcia_device {unsigned int irq; TYPE_1__** resource; int /*<<< orphan*/  dev; int /*<<< orphan*/ * prod_id; } ;
typedef  int /*<<< orphan*/  devname ;
struct TYPE_2__ {unsigned int start; } ;

/* Variables and functions */
#define  AVM_CARDTYPE_B1 130 
#define  AVM_CARDTYPE_M1 129 
#define  AVM_CARDTYPE_M2 128 
 int ENODEV ; 
 int /*<<< orphan*/  avmcs_configcheck ; 
 int /*<<< orphan*/  avmcs_release (struct pcmcia_device*) ; 
 int b1pcmcia_addcard_b1 (unsigned int,unsigned int) ; 
 int b1pcmcia_addcard_m1 (unsigned int,unsigned int) ; 
 int b1pcmcia_addcard_m2 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char*,char) ; 
 int stub1 (unsigned int,unsigned int) ; 

__attribute__((used)) static int avmcs_config(struct pcmcia_device *link)
{
	int i = -1;
	char devname[128];
	int cardtype;
	int (*addcard)(unsigned int port, unsigned irq);

	devname[0] = 0;
	if (link->prod_id[1])
		strlcpy(devname, link->prod_id[1], sizeof(devname));

	/*
	 * find IO port
	 */
	if (pcmcia_loop_config(link, avmcs_configcheck, NULL))
		return -ENODEV;

	do {
		if (!link->irq) {
			/* undo */
			pcmcia_disable_device(link);
			break;
		}

		/*
		 * configure the PCMCIA socket
		 */
		i = pcmcia_enable_device(link);
		if (i != 0) {
			pcmcia_disable_device(link);
			break;
		}

	} while (0);

	if (devname[0]) {
		char *s = strrchr(devname, ' ');
		if (!s)
			s = devname;
		else s++;
		if (strcmp("M1", s) == 0) {
			cardtype = AVM_CARDTYPE_M1;
		} else if (strcmp("M2", s) == 0) {
			cardtype = AVM_CARDTYPE_M2;
		} else {
			cardtype = AVM_CARDTYPE_B1;
		}
	} else
		cardtype = AVM_CARDTYPE_B1;

	/* If any step failed, release any partially configured state */
	if (i != 0) {
		avmcs_release(link);
		return -ENODEV;
	}


	switch (cardtype) {
	case AVM_CARDTYPE_M1: addcard = b1pcmcia_addcard_m1; break;
	case AVM_CARDTYPE_M2: addcard = b1pcmcia_addcard_m2; break;
	default:
	case AVM_CARDTYPE_B1: addcard = b1pcmcia_addcard_b1; break;
	}
	if ((i = (*addcard)(link->resource[0]->start, link->irq)) < 0) {
		dev_err(&link->dev,
			"avm_cs: failed to add AVM-Controller at i/o %#x, irq %d\n",
			(unsigned int) link->resource[0]->start, link->irq);
		avmcs_release(link);
		return -ENODEV;
	}
	return 0;

}