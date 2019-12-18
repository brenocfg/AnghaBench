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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct ath10k {TYPE_2__ hif; } ;
typedef  enum ath10k_firmware_mode { ____Placeholder_ath10k_firmware_mode } ath10k_firmware_mode ;
struct TYPE_3__ {int (* power_up ) (struct ath10k*,int) ;} ;

/* Variables and functions */
 int stub1 (struct ath10k*,int) ; 

__attribute__((used)) static inline int ath10k_hif_power_up(struct ath10k *ar,
				      enum ath10k_firmware_mode fw_mode)
{
	return ar->hif.ops->power_up(ar, fw_mode);
}