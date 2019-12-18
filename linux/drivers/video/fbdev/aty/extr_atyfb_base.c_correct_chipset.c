#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int pll_max; int mclk; int xclk; int ecp_max; } ;
struct atyfb_par {scalar_t__ pci_id; void* features; TYPE_1__ pll_limits; } ;
struct TYPE_5__ {scalar_t__ pci_id; char* name; int pll; int mclk; int xclk; int ecp_max; void* features; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_2__*) ; 
 void* ATI_CHIP_264GTB ; 
 void* ATI_CHIP_264VT ; 
 void* ATI_CHIP_264VT3 ; 
 void* ATI_CHIP_264VTB ; 
 int CFG_CHIP_REV ; 
 int CFG_CHIP_TYPE ; 
 int /*<<< orphan*/  CNFG_CHIP_ID ; 
 int ENODEV ; 
 void* M64F_MAGIC_POSTDIV ; 
#define  PCI_CHIP_MACH64CX 131 
#define  PCI_CHIP_MACH64GT 130 
#define  PCI_CHIP_MACH64GX 129 
#define  PCI_CHIP_MACH64VT 128 
 int /*<<< orphan*/  PRINTKI (char*,char const*,int,int) ; 
 TYPE_2__* aty_chips ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 

__attribute__((used)) static int correct_chipset(struct atyfb_par *par)
{
	u8 rev;
	u16 type;
	u32 chip_id;
	const char *name;
	int i;

	for (i = (int)ARRAY_SIZE(aty_chips) - 1; i >= 0; i--)
		if (par->pci_id == aty_chips[i].pci_id)
			break;

	if (i < 0)
		return -ENODEV;

	name = aty_chips[i].name;
	par->pll_limits.pll_max = aty_chips[i].pll;
	par->pll_limits.mclk = aty_chips[i].mclk;
	par->pll_limits.xclk = aty_chips[i].xclk;
	par->pll_limits.ecp_max = aty_chips[i].ecp_max;
	par->features = aty_chips[i].features;

	chip_id = aty_ld_le32(CNFG_CHIP_ID, par);
	type = chip_id & CFG_CHIP_TYPE;
	rev = (chip_id & CFG_CHIP_REV) >> 24;

	switch (par->pci_id) {
#ifdef CONFIG_FB_ATY_GX
	case PCI_CHIP_MACH64GX:
		if (type != 0x00d7)
			return -ENODEV;
		break;
	case PCI_CHIP_MACH64CX:
		if (type != 0x0057)
			return -ENODEV;
		break;
#endif
#ifdef CONFIG_FB_ATY_CT
	case PCI_CHIP_MACH64VT:
		switch (rev & 0x07) {
		case 0x00:
			switch (rev & 0xc0) {
			case 0x00:
				name = "ATI264VT (A3) (Mach64 VT)";
				par->pll_limits.pll_max = 170;
				par->pll_limits.mclk = 67;
				par->pll_limits.xclk = 67;
				par->pll_limits.ecp_max = 80;
				par->features = ATI_CHIP_264VT;
				break;
			case 0x40:
				name = "ATI264VT2 (A4) (Mach64 VT)";
				par->pll_limits.pll_max = 200;
				par->pll_limits.mclk = 67;
				par->pll_limits.xclk = 67;
				par->pll_limits.ecp_max = 80;
				par->features = ATI_CHIP_264VT | M64F_MAGIC_POSTDIV;
				break;
			}
			break;
		case 0x01:
			name = "ATI264VT3 (B1) (Mach64 VT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264VTB;
			break;
		case 0x02:
			name = "ATI264VT3 (B2) (Mach64 VT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264VT3;
			break;
		}
		break;
	case PCI_CHIP_MACH64GT:
		switch (rev & 0x07) {
		case 0x01:
			name = "3D RAGE II (Mach64 GT)";
			par->pll_limits.pll_max = 170;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264GTB;
			break;
		case 0x02:
			name = "3D RAGE II+ (Mach64 GT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 100;
			par->features = ATI_CHIP_264GTB;
			break;
		}
		break;
#endif
	}

	PRINTKI("%s [0x%04x rev 0x%02x]\n", name, type, rev);
	return 0;
}