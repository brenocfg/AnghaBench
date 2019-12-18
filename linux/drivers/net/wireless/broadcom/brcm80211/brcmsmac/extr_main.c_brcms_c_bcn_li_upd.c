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
struct brcms_c_info {int bcn_li_dtim; int bcn_li_bcn; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BCN_LI ; 
 int /*<<< orphan*/  brcms_b_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcms_c_bcn_li_upd(struct brcms_c_info *wlc)
{
	/* wake up every DTIM is the default */
	if (wlc->bcn_li_dtim == 1)
		brcms_b_write_shm(wlc->hw, M_BCN_LI, 0);
	else
		brcms_b_write_shm(wlc->hw, M_BCN_LI,
			      (wlc->bcn_li_dtim << 8) | wlc->bcn_li_bcn);
}