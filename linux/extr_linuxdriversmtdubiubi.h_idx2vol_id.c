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
struct ubi_device {int vtbl_slots; } ;

/* Variables and functions */
 int UBI_INTERNAL_VOL_START ; 

__attribute__((used)) static inline int idx2vol_id(const struct ubi_device *ubi, int idx)
{
	if (idx >= ubi->vtbl_slots)
		return idx - ubi->vtbl_slots + UBI_INTERNAL_VOL_START;
	else
		return idx;
}