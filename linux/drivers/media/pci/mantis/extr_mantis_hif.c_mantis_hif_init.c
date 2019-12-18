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
struct mantis_slot {int slave_cfg; } ;
struct mantis_pci {int /*<<< orphan*/  num; } ;
struct mantis_ca {int /*<<< orphan*/  ca_lock; struct mantis_pci* ca_priv; struct mantis_slot* slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  MANTIS_GPIF_IRQCFG ; 
 int MANTIS_MASK_BRRDY ; 
 int MANTIS_MASK_EXTIRQ ; 
 int MANTIS_MASK_OTHERR ; 
 int MANTIS_MASK_OVFLW ; 
 int MANTIS_MASK_WRACK ; 
 int MANTIS_MASK_WSTO ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mantis_hif_init(struct mantis_ca *ca)
{
	struct mantis_slot *slot = ca->slot;
	struct mantis_pci *mantis = ca->ca_priv;
	u32 irqcfg;

	slot[0].slave_cfg = 0x70773028;
	dprintk(MANTIS_ERROR, 1, "Adapter(%d) Initializing Mantis Host Interface", mantis->num);

	mutex_lock(&ca->ca_lock);
	irqcfg = mmread(MANTIS_GPIF_IRQCFG);
	irqcfg = MANTIS_MASK_BRRDY	|
		 MANTIS_MASK_WRACK	|
		 MANTIS_MASK_EXTIRQ	|
		 MANTIS_MASK_WSTO	|
		 MANTIS_MASK_OTHERR	|
		 MANTIS_MASK_OVFLW;

	mmwrite(irqcfg, MANTIS_GPIF_IRQCFG);
	mutex_unlock(&ca->ca_lock);

	return 0;
}