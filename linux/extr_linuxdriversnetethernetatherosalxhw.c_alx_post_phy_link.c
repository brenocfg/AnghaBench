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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct alx_hw {scalar_t__ link_speed; scalar_t__ lnk_patch; } ;

/* Variables and functions */
 scalar_t__ ALX_AFE_10BT_100M_TH ; 
 int /*<<< orphan*/  ALX_AGC_2_VGA ; 
 scalar_t__ ALX_AGC_LONG100M_LIMT ; 
 scalar_t__ ALX_AGC_LONG1G_LIMT ; 
 scalar_t__ ALX_AZ_ANADECT_DEF ; 
 scalar_t__ ALX_AZ_ANADECT_LONG ; 
 int /*<<< orphan*/  ALX_CLDCTRL6_CAB_LEN ; 
 scalar_t__ ALX_CLDCTRL6_CAB_LEN_SHORT100M ; 
 scalar_t__ ALX_CLDCTRL6_CAB_LEN_SHORT1G ; 
 scalar_t__ ALX_GET_FIELD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALX_MIIDBG_AGC ; 
 int /*<<< orphan*/  ALX_MIIDBG_AZ_ANADECT ; 
 int /*<<< orphan*/  ALX_MIIDBG_MSE16DB ; 
 int /*<<< orphan*/  ALX_MIIDBG_MSE20DB ; 
 int /*<<< orphan*/  ALX_MIIEXT_AFE ; 
 int /*<<< orphan*/  ALX_MIIEXT_ANEG ; 
 int /*<<< orphan*/  ALX_MIIEXT_CLDCTRL6 ; 
 int /*<<< orphan*/  ALX_MIIEXT_PCS ; 
 scalar_t__ ALX_MSE16DB_DOWN ; 
 scalar_t__ ALX_MSE16DB_UP ; 
 int /*<<< orphan*/  ALX_MSE20DB_TH ; 
 int /*<<< orphan*/  ALX_MSE20DB_TH_DEF ; 
 int /*<<< orphan*/  ALX_MSE20DB_TH_HI ; 
 scalar_t__ ALX_REV_B0 ; 
 int /*<<< orphan*/  ALX_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_UNKNOWN ; 
 scalar_t__ alx_hw_revision (struct alx_hw*) ; 
 int /*<<< orphan*/  alx_is_rev_a (scalar_t__) ; 
 int /*<<< orphan*/  alx_read_phy_dbg (struct alx_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  alx_read_phy_ext (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  alx_write_phy_dbg (struct alx_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  alx_write_phy_ext (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void alx_post_phy_link(struct alx_hw *hw)
{
	u16 phy_val, len, agc;
	u8 revid = alx_hw_revision(hw);
	bool adj_th = revid == ALX_REV_B0;

	if (revid != ALX_REV_B0 && !alx_is_rev_a(revid))
		return;

	/* 1000BT/AZ, wrong cable length */
	if (hw->link_speed != SPEED_UNKNOWN) {
		alx_read_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL6,
				 &phy_val);
		len = ALX_GET_FIELD(phy_val, ALX_CLDCTRL6_CAB_LEN);
		alx_read_phy_dbg(hw, ALX_MIIDBG_AGC, &phy_val);
		agc = ALX_GET_FIELD(phy_val, ALX_AGC_2_VGA);

		if ((hw->link_speed == SPEED_1000 &&
		     (len > ALX_CLDCTRL6_CAB_LEN_SHORT1G ||
		      (len == 0 && agc > ALX_AGC_LONG1G_LIMT))) ||
		    (hw->link_speed == SPEED_100 &&
		     (len > ALX_CLDCTRL6_CAB_LEN_SHORT100M ||
		      (len == 0 && agc > ALX_AGC_LONG100M_LIMT)))) {
			alx_write_phy_dbg(hw, ALX_MIIDBG_AZ_ANADECT,
					  ALX_AZ_ANADECT_LONG);
			alx_read_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
					 &phy_val);
			alx_write_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
					  phy_val | ALX_AFE_10BT_100M_TH);
		} else {
			alx_write_phy_dbg(hw, ALX_MIIDBG_AZ_ANADECT,
					  ALX_AZ_ANADECT_DEF);
			alx_read_phy_ext(hw, ALX_MIIEXT_ANEG,
					 ALX_MIIEXT_AFE, &phy_val);
			alx_write_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
					  phy_val & ~ALX_AFE_10BT_100M_TH);
		}

		/* threshold adjust */
		if (adj_th && hw->lnk_patch) {
			if (hw->link_speed == SPEED_100) {
				alx_write_phy_dbg(hw, ALX_MIIDBG_MSE16DB,
						  ALX_MSE16DB_UP);
			} else if (hw->link_speed == SPEED_1000) {
				/*
				 * Giga link threshold, raise the tolerance of
				 * noise 50%
				 */
				alx_read_phy_dbg(hw, ALX_MIIDBG_MSE20DB,
						 &phy_val);
				ALX_SET_FIELD(phy_val, ALX_MSE20DB_TH,
					      ALX_MSE20DB_TH_HI);
				alx_write_phy_dbg(hw, ALX_MIIDBG_MSE20DB,
						  phy_val);
			}
		}
	} else {
		alx_read_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
				 &phy_val);
		alx_write_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
				  phy_val & ~ALX_AFE_10BT_100M_TH);

		if (adj_th && hw->lnk_patch) {
			alx_write_phy_dbg(hw, ALX_MIIDBG_MSE16DB,
					  ALX_MSE16DB_DOWN);
			alx_read_phy_dbg(hw, ALX_MIIDBG_MSE20DB, &phy_val);
			ALX_SET_FIELD(phy_val, ALX_MSE20DB_TH,
				      ALX_MSE20DB_TH_DEF);
			alx_write_phy_dbg(hw, ALX_MIIDBG_MSE20DB, phy_val);
		}
	}
}