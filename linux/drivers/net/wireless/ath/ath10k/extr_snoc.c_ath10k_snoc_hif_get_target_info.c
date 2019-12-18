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
struct bmi_target_info {void* type; void* version; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 void* ATH10K_HW_WCN3990 ; 

__attribute__((used)) static int ath10k_snoc_hif_get_target_info(struct ath10k *ar,
					   struct bmi_target_info *target_info)
{
	target_info->version = ATH10K_HW_WCN3990;
	target_info->type = ATH10K_HW_WCN3990;

	return 0;
}