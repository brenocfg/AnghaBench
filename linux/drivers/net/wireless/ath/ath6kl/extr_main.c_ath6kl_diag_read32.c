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
typedef  int /*<<< orphan*/  u32 ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int ath6kl_hif_diag_read32 (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,int) ; 

int ath6kl_diag_read32(struct ath6kl *ar, u32 address, u32 *value)
{
	int ret;

	ret = ath6kl_hif_diag_read32(ar, address, value);
	if (ret) {
		ath6kl_warn("failed to read32 through diagnose window: %d\n",
			    ret);
		return ret;
	}

	return 0;
}