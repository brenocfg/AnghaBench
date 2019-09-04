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
typedef  int u8 ;
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  dbell_fire_entries (size_t) ; 
 size_t max_notify_idx ; 

void vmci_dbell_scan_notification_entries(u8 *bitmap)
{
	u32 idx;

	for (idx = 0; idx < max_notify_idx; idx++) {
		if (bitmap[idx] & 0x1) {
			bitmap[idx] &= ~1;
			dbell_fire_entries(idx);
		}
	}
}