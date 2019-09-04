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
struct md_rdev {scalar_t__ raid_disk; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  Journal ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
slot_show(struct md_rdev *rdev, char *page)
{
	if (test_bit(Journal, &rdev->flags))
		return sprintf(page, "journal\n");
	else if (rdev->raid_disk < 0)
		return sprintf(page, "none\n");
	else
		return sprintf(page, "%d\n", rdev->raid_disk);
}