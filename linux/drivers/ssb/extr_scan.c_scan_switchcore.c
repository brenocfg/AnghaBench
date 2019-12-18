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
struct ssb_bus {int bustype; } ;

/* Variables and functions */
#define  SSB_BUSTYPE_PCI 131 
#define  SSB_BUSTYPE_PCMCIA 130 
#define  SSB_BUSTYPE_SDIO 129 
#define  SSB_BUSTYPE_SSB 128 
 int ssb_pci_switch_coreidx (struct ssb_bus*,int /*<<< orphan*/ ) ; 
 int ssb_pcmcia_switch_coreidx (struct ssb_bus*,int /*<<< orphan*/ ) ; 
 int ssb_sdio_scan_switch_coreidx (struct ssb_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scan_switchcore(struct ssb_bus *bus, u8 coreidx)
{
	switch (bus->bustype) {
	case SSB_BUSTYPE_SSB:
		break;
	case SSB_BUSTYPE_PCI:
		return ssb_pci_switch_coreidx(bus, coreidx);
	case SSB_BUSTYPE_PCMCIA:
		return ssb_pcmcia_switch_coreidx(bus, coreidx);
	case SSB_BUSTYPE_SDIO:
		return ssb_sdio_scan_switch_coreidx(bus, coreidx);
	}
	return 0;
}