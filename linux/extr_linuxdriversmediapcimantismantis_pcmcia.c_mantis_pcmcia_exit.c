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
struct mantis_ca {struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int MANTIS_CARD_PLUGIN ; 
 int MANTIS_CARD_PLUGOUT ; 
 int /*<<< orphan*/  MANTIS_GPIF_STATUS ; 
 int /*<<< orphan*/  MANTIS_INT_IRQ0 ; 
 int /*<<< orphan*/  mantis_mask_ints (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 

void mantis_pcmcia_exit(struct mantis_ca *ca)
{
	struct mantis_pci *mantis = ca->ca_priv;

	mmwrite(mmread(MANTIS_GPIF_STATUS) & (~MANTIS_CARD_PLUGOUT | ~MANTIS_CARD_PLUGIN), MANTIS_GPIF_STATUS);
	mantis_mask_ints(mantis, MANTIS_INT_IRQ0);
}