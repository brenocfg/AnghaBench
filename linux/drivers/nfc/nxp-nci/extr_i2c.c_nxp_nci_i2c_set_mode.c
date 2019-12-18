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
struct nxp_nci_i2c_phy {scalar_t__ hard_fault; int /*<<< orphan*/  gpiod_en; int /*<<< orphan*/  gpiod_fw; } ;
typedef  enum nxp_nci_mode { ____Placeholder_nxp_nci_mode } nxp_nci_mode ;

/* Variables and functions */
 int NXP_NCI_MODE_COLD ; 
 int NXP_NCI_MODE_FW ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int nxp_nci_i2c_set_mode(void *phy_id,
				    enum nxp_nci_mode mode)
{
	struct nxp_nci_i2c_phy *phy = (struct nxp_nci_i2c_phy *) phy_id;

	gpiod_set_value(phy->gpiod_fw, (mode == NXP_NCI_MODE_FW) ? 1 : 0);
	gpiod_set_value(phy->gpiod_en, (mode != NXP_NCI_MODE_COLD) ? 1 : 0);
	usleep_range(10000, 15000);

	if (mode == NXP_NCI_MODE_COLD)
		phy->hard_fault = 0;

	return 0;
}