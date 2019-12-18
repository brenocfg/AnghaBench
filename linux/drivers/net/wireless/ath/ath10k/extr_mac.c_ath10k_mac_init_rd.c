#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  current_rd; } ;
struct TYPE_4__ {TYPE_1__ regulatory; } ;
struct ath10k {TYPE_2__ ath_common; int /*<<< orphan*/  hw_eeprom_rd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int ath10k_mac_get_wrdd_regulatory (struct ath10k*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_mac_init_rd(struct ath10k *ar)
{
	int ret;
	u16 rd;

	ret = ath10k_mac_get_wrdd_regulatory(ar, &rd);
	if (ret) {
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "fallback to eeprom programmed regulatory settings\n");
		rd = ar->hw_eeprom_rd;
	}

	ar->ath_common.regulatory.current_rd = rd;
	return 0;
}