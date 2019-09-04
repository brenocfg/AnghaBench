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
struct mantis_pci {int dummy; } ;
struct mantis_ca {int /*<<< orphan*/  en50221; struct mantis_pci* ca_priv; } ;
struct dvb_ca_en50221 {struct mantis_ca* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_PCMCIA_RESET ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  dvb_ca_en50221_camready_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mantis_ca_slot_reset(struct dvb_ca_en50221 *en50221, int slot)
{
	struct mantis_ca *ca = en50221->data;
	struct mantis_pci *mantis = ca->ca_priv;

	dprintk(MANTIS_DEBUG, 1, "Slot(%d): Slot RESET", slot);
	udelay(500); /* Wait.. */
	mmwrite(0xda, MANTIS_PCMCIA_RESET); /* Leading edge assert */
	udelay(500);
	mmwrite(0x00, MANTIS_PCMCIA_RESET); /* Trailing edge deassert */
	msleep(1000);
	dvb_ca_en50221_camready_irq(&ca->en50221, 0);

	return 0;
}