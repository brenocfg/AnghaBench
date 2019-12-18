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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ seq_num; int hb_pending; } ;
struct ath6kl {TYPE_1__ fw_recovery; } ;

/* Variables and functions */

void ath6kl_recovery_hb_event(struct ath6kl *ar, u32 cookie)
{
	if (cookie == ar->fw_recovery.seq_num)
		ar->fw_recovery.hb_pending = false;
}