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
typedef  int u8 ;
typedef  int u32 ;
struct mantis_pci {int num; } ;
struct mantis_ca {int /*<<< orphan*/  ca_lock; struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  MANTIS_GPIF_ADDR ; 
 int /*<<< orphan*/  MANTIS_GPIF_BRADDR ; 
 int /*<<< orphan*/  MANTIS_GPIF_BRBYTES ; 
 int /*<<< orphan*/  MANTIS_GPIF_DIN ; 
 int MANTIS_GPIF_HIFRDWRN ; 
 int MANTIS_GPIF_PCMCIAIOM ; 
 int MANTIS_GPIF_PCMCIAREG ; 
 int MANTIS_HIF_STATUS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ mantis_hif_sbuf_opdone_wait (struct mantis_ca*) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int mantis_hif_read_iom(struct mantis_ca *ca, u32 addr)
{
	struct mantis_pci *mantis = ca->ca_priv;
	u32 data, hif_addr = 0;

	dprintk(MANTIS_DEBUG, 1, "Adapter(%d) Slot(0): Request HIF I/O Read", mantis->num);
	mutex_lock(&ca->ca_lock);
	hif_addr &= ~MANTIS_GPIF_PCMCIAREG;
	hif_addr |=  MANTIS_GPIF_PCMCIAIOM;
	hif_addr |=  MANTIS_HIF_STATUS;
	hif_addr |=  addr;

	mmwrite(hif_addr, MANTIS_GPIF_BRADDR);
	mmwrite(1, MANTIS_GPIF_BRBYTES);
	udelay(20);
	mmwrite(hif_addr | MANTIS_GPIF_HIFRDWRN, MANTIS_GPIF_ADDR);

	if (mantis_hif_sbuf_opdone_wait(ca) != 0) {
		dprintk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): HIF Smart Buffer operation failed", mantis->num);
		mutex_unlock(&ca->ca_lock);
		return -EREMOTEIO;
	}
	data = mmread(MANTIS_GPIF_DIN);
	dprintk(MANTIS_DEBUG, 1, "I/O Read: 0x%02x", data);
	udelay(50);
	mutex_unlock(&ca->ca_lock);

	return (u8) data;
}