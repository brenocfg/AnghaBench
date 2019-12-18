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
typedef  void* u8 ;
struct ath9k_hw_mci {int bt_version_known; void* bt_ver_minor; void* bt_ver_major; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCI ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,void*) ; 

void ar9003_mci_set_bt_version(struct ath_hw *ah, u8 major, u8 minor)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->bt_ver_major = major;
	mci->bt_ver_minor = minor;
	mci->bt_version_known = true;
	ath_dbg(ath9k_hw_common(ah), MCI, "MCI BT version set: %d.%d\n",
		mci->bt_ver_major, mci->bt_ver_minor);
}