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
typedef  size_t uint ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mimophytbl_info_rev0 ; 
 int /*<<< orphan*/ * mimophytbl_info_rev16 ; 
 int /*<<< orphan*/ * mimophytbl_info_rev3 ; 
 int /*<<< orphan*/ * mimophytbl_info_rev7 ; 
 size_t mimophytbl_info_sz_rev0 ; 
 size_t mimophytbl_info_sz_rev16 ; 
 size_t mimophytbl_info_sz_rev3 ; 
 size_t mimophytbl_info_sz_rev7 ; 
 int /*<<< orphan*/  wlc_phy_write_table_nphy (struct brcms_phy*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
wlc_phy_static_table_download_nphy(struct brcms_phy *pi)
{
	uint idx;

	if (NREV_GE(pi->pubpi.phy_rev, 16)) {
		for (idx = 0; idx < mimophytbl_info_sz_rev16; idx++)
			wlc_phy_write_table_nphy(pi,
						 &mimophytbl_info_rev16[idx]);
	} else if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		for (idx = 0; idx < mimophytbl_info_sz_rev7; idx++)
			wlc_phy_write_table_nphy(pi,
						 &mimophytbl_info_rev7[idx]);
	} else if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		for (idx = 0; idx < mimophytbl_info_sz_rev3; idx++)
			wlc_phy_write_table_nphy(pi,
						 &mimophytbl_info_rev3[idx]);
	} else {
		for (idx = 0; idx < mimophytbl_info_sz_rev0; idx++)
			wlc_phy_write_table_nphy(pi,
						 &mimophytbl_info_rev0[idx]);
	}
}