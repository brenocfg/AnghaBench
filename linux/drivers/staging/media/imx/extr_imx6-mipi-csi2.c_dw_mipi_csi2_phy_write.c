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
typedef  int u32 ;
struct csi2_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CSI2_PHY_TST_CTRL0 ; 
 scalar_t__ CSI2_PHY_TST_CTRL1 ; 
 int PHY_TESTCLK ; 
 int PHY_TESTCLR ; 
 int PHY_TESTEN ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void dw_mipi_csi2_phy_write(struct csi2_dev *csi2,
				   u32 test_code, u32 test_data)
{
	/* Clear PHY test interface */
	writel(PHY_TESTCLR, csi2->base + CSI2_PHY_TST_CTRL0);
	writel(0x0, csi2->base + CSI2_PHY_TST_CTRL1);
	writel(0x0, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Raise test interface strobe signal */
	writel(PHY_TESTCLK, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Configure address write on falling edge and lower strobe signal */
	writel(PHY_TESTEN | test_code, csi2->base + CSI2_PHY_TST_CTRL1);
	writel(0x0, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Configure data write on rising edge and raise strobe signal */
	writel(test_data, csi2->base + CSI2_PHY_TST_CTRL1);
	writel(PHY_TESTCLK, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Clear strobe signal */
	writel(0x0, csi2->base + CSI2_PHY_TST_CTRL0);
}