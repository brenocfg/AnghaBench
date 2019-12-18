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
struct ath10k {scalar_t__ hw_rev; } ;

/* Variables and functions */
 scalar_t__ ATH10K_HW_QCA4019 ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 

__attribute__((used)) static int ath10k_ahb_get_num_banks(struct ath10k *ar)
{
	if (ar->hw_rev == ATH10K_HW_QCA4019)
		return 1;

	ath10k_warn(ar, "unknown number of banks, assuming 1\n");
	return 1;
}