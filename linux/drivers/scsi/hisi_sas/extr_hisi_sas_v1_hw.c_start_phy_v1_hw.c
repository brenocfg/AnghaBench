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
struct hisi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_id_frame_v1_hw (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  config_phy_opt_mode_v1_hw (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  config_tx_tfe_autoneg_v1_hw (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  enable_phy_v1_hw (struct hisi_hba*,int) ; 

__attribute__((used)) static void start_phy_v1_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	config_id_frame_v1_hw(hisi_hba, phy_no);
	config_phy_opt_mode_v1_hw(hisi_hba, phy_no);
	config_tx_tfe_autoneg_v1_hw(hisi_hba, phy_no);
	enable_phy_v1_hw(hisi_hba, phy_no);
}