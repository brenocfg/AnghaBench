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
struct md_rdev {unsigned long long recovery_offset; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  In_sync ; 
 unsigned long long MaxSector ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t recovery_start_show(struct md_rdev *rdev, char *page)
{
	unsigned long long recovery_start = rdev->recovery_offset;

	if (test_bit(In_sync, &rdev->flags) ||
	    recovery_start == MaxSector)
		return sprintf(page, "none\n");

	return sprintf(page, "%llu\n", recovery_start);
}