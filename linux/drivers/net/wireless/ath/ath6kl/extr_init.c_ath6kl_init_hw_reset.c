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
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  RESET_CONTROL_ADDRESS ; 
 int /*<<< orphan*/  RESET_CONTROL_COLD_RST ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int ath6kl_diag_write32 (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_init_hw_reset(struct ath6kl *ar)
{
	ath6kl_dbg(ATH6KL_DBG_BOOT, "cold resetting the device");

	return ath6kl_diag_write32(ar, RESET_CONTROL_ADDRESS,
				   cpu_to_le32(RESET_CONTROL_COLD_RST));
}