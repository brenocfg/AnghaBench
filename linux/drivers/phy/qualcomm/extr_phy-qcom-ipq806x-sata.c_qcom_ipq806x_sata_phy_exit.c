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
struct qcom_ipq806x_sata_phy {scalar_t__ mmio; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ SATA_PHY_P0_PARAM4 ; 
 int SATA_PHY_RESET ; 
 struct qcom_ipq806x_sata_phy* phy_get_drvdata (struct phy*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int qcom_ipq806x_sata_phy_exit(struct phy *generic_phy)
{
	struct qcom_ipq806x_sata_phy *phy = phy_get_drvdata(generic_phy);
	u32 reg;

	/* Setting PHY_RESET to 1 */
	reg = readl_relaxed(phy->mmio + SATA_PHY_P0_PARAM4);
	reg = reg | SATA_PHY_RESET;
	writel_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM4);

	return 0;
}