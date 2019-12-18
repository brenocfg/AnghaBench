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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mantis_slot {int /*<<< orphan*/  slave_cfg; } ;
struct mantis_pci {int /*<<< orphan*/  num; } ;
struct mantis_ca {int /*<<< orphan*/  ca_lock; struct mantis_pci* ca_priv; struct mantis_slot* slot; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  MANTIS_GPIF_ADDR ; 
 int /*<<< orphan*/  MANTIS_GPIF_CFGSLA ; 
 int /*<<< orphan*/  MANTIS_GPIF_DOUT ; 
 int /*<<< orphan*/  MANTIS_GPIF_HIFRDWRN ; 
 int /*<<< orphan*/  MANTIS_GPIF_PCMCIAIOM ; 
 int /*<<< orphan*/  MANTIS_GPIF_PCMCIAREG ; 
 int /*<<< orphan*/  MANTIS_HIF_STATUS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ mantis_hif_write_wait (struct mantis_ca*) ; 
 int /*<<< orphan*/  mmwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mantis_hif_write_mem(struct mantis_ca *ca, u32 addr, u8 data)
{
	struct mantis_slot *slot = ca->slot;
	struct mantis_pci *mantis = ca->ca_priv;
	u32 hif_addr = 0;

	dprintk(MANTIS_DEBUG, 1, "Adapter(%d) Slot(0): Request HIF Mem Write", mantis->num);
	mutex_lock(&ca->ca_lock);
	hif_addr &= ~MANTIS_GPIF_HIFRDWRN;
	hif_addr &= ~MANTIS_GPIF_PCMCIAREG;
	hif_addr &= ~MANTIS_GPIF_PCMCIAIOM;
	hif_addr |=  MANTIS_HIF_STATUS;
	hif_addr |=  addr;

	mmwrite(slot->slave_cfg, MANTIS_GPIF_CFGSLA); /* Slot0 alone for now */
	mmwrite(hif_addr, MANTIS_GPIF_ADDR);
	mmwrite(data, MANTIS_GPIF_DOUT);

	if (mantis_hif_write_wait(ca) != 0) {
		dprintk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): HIF Smart Buffer operation failed", mantis->num);
		mutex_unlock(&ca->ca_lock);
		return -EREMOTEIO;
	}
	dprintk(MANTIS_DEBUG, 1, "Mem Write: (0x%02x to 0x%02x)", data, addr);
	mutex_unlock(&ca->ca_lock);

	return 0;
}