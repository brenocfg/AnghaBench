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
typedef  int u32 ;
struct device {int dummy; } ;
struct altera_pcie {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int RP_RXCPL_EOP ; 
 int RP_RXCPL_SOP ; 
 int /*<<< orphan*/  S10_RP_RXCPL_REG ; 
 int /*<<< orphan*/  S10_RP_RXCPL_STATUS ; 
 int TLP_BYTE_COUNT (int) ; 
 int TLP_COMP_STATUS (int) ; 
 int TLP_LOOP ; 
 int cra_readl (struct altera_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int s10_tlp_read_packet(struct altera_pcie *pcie, u32 *value)
{
	u32 ctrl;
	u32 comp_status;
	u32 dw[4];
	u32 count;
	struct device *dev = &pcie->pdev->dev;

	for (count = 0; count < TLP_LOOP; count++) {
		ctrl = cra_readl(pcie, S10_RP_RXCPL_STATUS);
		if (ctrl & RP_RXCPL_SOP) {
			/* Read first DW */
			dw[0] = cra_readl(pcie, S10_RP_RXCPL_REG);
			break;
		}

		udelay(5);
	}

	/* SOP detection failed, return error */
	if (count == TLP_LOOP)
		return PCIBIOS_DEVICE_NOT_FOUND;

	count = 1;

	/* Poll for EOP */
	while (count < ARRAY_SIZE(dw)) {
		ctrl = cra_readl(pcie, S10_RP_RXCPL_STATUS);
		dw[count++] = cra_readl(pcie, S10_RP_RXCPL_REG);
		if (ctrl & RP_RXCPL_EOP) {
			comp_status = TLP_COMP_STATUS(dw[1]);
			if (comp_status)
				return PCIBIOS_DEVICE_NOT_FOUND;

			if (value && TLP_BYTE_COUNT(dw[1]) == sizeof(u32) &&
			    count == 4)
				*value = dw[3];

			return PCIBIOS_SUCCESSFUL;
		}
	}

	dev_warn(dev, "Malformed TLP packet\n");

	return PCIBIOS_DEVICE_NOT_FOUND;
}