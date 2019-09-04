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
typedef  int /*<<< orphan*/  u32 ;
struct mantis_pci {int /*<<< orphan*/  num; } ;
struct mantis_ca {int /*<<< orphan*/  ca_lock; struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  MANTIS_GPIF_IRQCFG ; 
 int /*<<< orphan*/  MANTIS_MASK_BRRDY ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mantis_hif_exit(struct mantis_ca *ca)
{
	struct mantis_pci *mantis = ca->ca_priv;
	u32 irqcfg;

	dprintk(MANTIS_ERROR, 1, "Adapter(%d) Exiting Mantis Host Interface", mantis->num);
	mutex_lock(&ca->ca_lock);
	irqcfg = mmread(MANTIS_GPIF_IRQCFG);
	irqcfg &= ~MANTIS_MASK_BRRDY;
	mmwrite(irqcfg, MANTIS_GPIF_IRQCFG);
	mutex_unlock(&ca->ca_lock);
}