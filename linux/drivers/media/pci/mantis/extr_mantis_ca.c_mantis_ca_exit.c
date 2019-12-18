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
struct mantis_pci {struct mantis_ca* mantis_ca; } ;
struct mantis_ca {int /*<<< orphan*/  en50221; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  dvb_ca_en50221_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mantis_ca*) ; 
 int /*<<< orphan*/  mantis_evmgr_exit (struct mantis_ca*) ; 

void mantis_ca_exit(struct mantis_pci *mantis)
{
	struct mantis_ca *ca = mantis->mantis_ca;

	dprintk(MANTIS_DEBUG, 1, "Mantis CA exit");
	if (!ca)
		return;

	mantis_evmgr_exit(ca);
	dprintk(MANTIS_ERROR, 1, "Unregistering EN50221 device");
	dvb_ca_en50221_release(&ca->en50221);

	kfree(ca);
}