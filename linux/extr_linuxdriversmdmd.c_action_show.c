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
struct mddev {unsigned long recovery; scalar_t__ reshape_position; int /*<<< orphan*/  ro; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_CHECK ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RECOVER ; 
 int /*<<< orphan*/  MD_RECOVERY_REQUESTED ; 
 int /*<<< orphan*/  MD_RECOVERY_RESHAPE ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 int /*<<< orphan*/  MD_RECOVERY_SYNC ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t
action_show(struct mddev *mddev, char *page)
{
	char *type = "idle";
	unsigned long recovery = mddev->recovery;
	if (test_bit(MD_RECOVERY_FROZEN, &recovery))
		type = "frozen";
	else if (test_bit(MD_RECOVERY_RUNNING, &recovery) ||
	    (!mddev->ro && test_bit(MD_RECOVERY_NEEDED, &recovery))) {
		if (test_bit(MD_RECOVERY_RESHAPE, &recovery))
			type = "reshape";
		else if (test_bit(MD_RECOVERY_SYNC, &recovery)) {
			if (!test_bit(MD_RECOVERY_REQUESTED, &recovery))
				type = "resync";
			else if (test_bit(MD_RECOVERY_CHECK, &recovery))
				type = "check";
			else
				type = "repair";
		} else if (test_bit(MD_RECOVERY_RECOVER, &recovery))
			type = "recover";
		else if (mddev->reshape_position != MaxSector)
			type = "reshape";
	}
	return sprintf(page, "%s\n", type);
}