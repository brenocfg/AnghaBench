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
typedef  int u32 ;
struct mantis_pci {int /*<<< orphan*/  num; } ;
struct mantis_ca {scalar_t__ slot_state; struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_CARD_RESET ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_GPIF_IRQCFG ; 
 int MANTIS_MASK_PLUGIN ; 
 int MANTIS_MASK_PLUGOUT ; 
 scalar_t__ MODULE_INSERTED ; 
 scalar_t__ MODULE_XTRACTED ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void mantis_event_cam_plugin(struct mantis_ca *ca)
{
	struct mantis_pci *mantis = ca->ca_priv;

	u32 gpif_irqcfg;

	if (ca->slot_state == MODULE_XTRACTED) {
		dprintk(MANTIS_DEBUG, 1, "Event: CAM Plugged IN: Adapter(%d) Slot(0)", mantis->num);
		udelay(50);
		mmwrite(0xda000000, MANTIS_CARD_RESET);
		gpif_irqcfg  = mmread(MANTIS_GPIF_IRQCFG);
		gpif_irqcfg |= MANTIS_MASK_PLUGOUT;
		gpif_irqcfg &= ~MANTIS_MASK_PLUGIN;
		mmwrite(gpif_irqcfg, MANTIS_GPIF_IRQCFG);
		udelay(500);
		ca->slot_state = MODULE_INSERTED;
	}
	udelay(100);
}