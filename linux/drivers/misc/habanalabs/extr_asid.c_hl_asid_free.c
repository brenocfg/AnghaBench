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
struct TYPE_2__ {unsigned long max_asid; } ;
struct hl_device {int /*<<< orphan*/  asid_bitmap; TYPE_1__ asic_prop; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*,unsigned long) ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 

void hl_asid_free(struct hl_device *hdev, unsigned long asid)
{
	if (WARN((asid == 0 || asid >= hdev->asic_prop.max_asid),
						"Invalid ASID %lu", asid))
		return;
	clear_bit(asid, hdev->asid_bitmap);
}