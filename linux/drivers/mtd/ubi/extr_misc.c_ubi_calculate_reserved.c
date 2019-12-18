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
struct ubi_device {scalar_t__ beb_rsvd_level; scalar_t__ bad_peb_limit; scalar_t__ bad_peb_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*,scalar_t__,scalar_t__) ; 

void ubi_calculate_reserved(struct ubi_device *ubi)
{
	/*
	 * Calculate the actual number of PEBs currently needed to be reserved
	 * for future bad eraseblock handling.
	 */
	ubi->beb_rsvd_level = ubi->bad_peb_limit - ubi->bad_peb_count;
	if (ubi->beb_rsvd_level < 0) {
		ubi->beb_rsvd_level = 0;
		ubi_warn(ubi, "number of bad PEBs (%d) is above the expected limit (%d), not reserving any PEBs for bad PEB handling, will use available PEBs (if any)",
			 ubi->bad_peb_count, ubi->bad_peb_limit);
	}
}