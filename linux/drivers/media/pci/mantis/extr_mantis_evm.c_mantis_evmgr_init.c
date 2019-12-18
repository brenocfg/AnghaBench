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
struct mantis_ca {int /*<<< orphan*/  hif_evm_work; struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mantis_hif_init (struct mantis_ca*) ; 
 int /*<<< orphan*/  mantis_hifevm_work ; 
 int /*<<< orphan*/  mantis_pcmcia_init (struct mantis_ca*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int mantis_evmgr_init(struct mantis_ca *ca)
{
	struct mantis_pci *mantis = ca->ca_priv;

	dprintk(MANTIS_DEBUG, 1, "Initializing Mantis Host I/F Event manager");
	INIT_WORK(&ca->hif_evm_work, mantis_hifevm_work);
	mantis_pcmcia_init(ca);
	schedule_work(&ca->hif_evm_work);
	mantis_hif_init(ca);
	return 0;
}