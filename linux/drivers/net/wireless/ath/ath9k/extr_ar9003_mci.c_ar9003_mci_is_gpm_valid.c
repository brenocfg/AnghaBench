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
struct ath9k_hw_mci {scalar_t__ gpm_buf; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int MCI_GPM_INVALID ; 
 int MCI_GPM_RSVD_PATTERN ; 
 int MCI_GPM_TYPE (int*) ; 

__attribute__((used)) static bool ar9003_mci_is_gpm_valid(struct ath_hw *ah, u32 msg_index)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *payload;
	u32 recv_type, offset;

	if (msg_index == MCI_GPM_INVALID)
		return false;

	offset = msg_index << 4;

	payload = (u32 *)(mci->gpm_buf + offset);
	recv_type = MCI_GPM_TYPE(payload);

	if (recv_type == MCI_GPM_RSVD_PATTERN)
		return false;

	return true;
}