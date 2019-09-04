#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ilk_disable; int /*<<< orphan*/  cfg; } ;
union nps_core_gbl_vfcfg {unsigned long long value; TYPE_1__ s; } ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_CORE_CONTROL ; 
 int /*<<< orphan*/  NPS_CORE_GBL_VFCFG ; 
 int /*<<< orphan*/  PF_MODE ; 
 int /*<<< orphan*/  enable_nps_interrupts (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_pkt_input_rings (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_pkt_solicit_ports (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,unsigned long long) ; 

void nitrox_config_nps_unit(struct nitrox_device *ndev)
{
	union nps_core_gbl_vfcfg core_gbl_vfcfg;

	/* endian control information */
	nitrox_write_csr(ndev, NPS_CORE_CONTROL, 1ULL);

	/* disable ILK interface */
	core_gbl_vfcfg.value = 0;
	core_gbl_vfcfg.s.ilk_disable = 1;
	core_gbl_vfcfg.s.cfg = PF_MODE;
	nitrox_write_csr(ndev, NPS_CORE_GBL_VFCFG, core_gbl_vfcfg.value);
	/* config input and solicit ports */
	nitrox_config_pkt_input_rings(ndev);
	nitrox_config_pkt_solicit_ports(ndev);

	/* enable interrupts */
	enable_nps_interrupts(ndev);
}