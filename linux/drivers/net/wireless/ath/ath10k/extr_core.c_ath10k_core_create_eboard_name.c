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
struct TYPE_4__ {int /*<<< orphan*/  bmi_eboard_id; int /*<<< orphan*/  bmi_chip_id; scalar_t__ bmi_ids_valid; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;
struct ath10k {TYPE_2__ id; TYPE_1__ hif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_bus_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_core_create_eboard_name(struct ath10k *ar, char *name,
					  size_t name_len)
{
	if (ar->id.bmi_ids_valid) {
		scnprintf(name, name_len,
			  "bus=%s,bmi-chip-id=%d,bmi-eboard-id=%d",
			  ath10k_bus_str(ar->hif.bus),
			  ar->id.bmi_chip_id,
			  ar->id.bmi_eboard_id);

		ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot using eboard name '%s'\n", name);
		return 0;
	}
	/* Fallback if returned board id is zero */
	return -1;
}