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
struct mddev {TYPE_1__* pers; scalar_t__ bitmap; int /*<<< orphan*/  flags; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ sync_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_HAS_JOURNAL ; 
 int /*<<< orphan*/  MD_HAS_PPL ; 
 int sprintf (char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
consistency_policy_show(struct mddev *mddev, char *page)
{
	int ret;

	if (test_bit(MD_HAS_JOURNAL, &mddev->flags)) {
		ret = sprintf(page, "journal\n");
	} else if (test_bit(MD_HAS_PPL, &mddev->flags)) {
		ret = sprintf(page, "ppl\n");
	} else if (mddev->bitmap) {
		ret = sprintf(page, "bitmap\n");
	} else if (mddev->pers) {
		if (mddev->pers->sync_request)
			ret = sprintf(page, "resync\n");
		else
			ret = sprintf(page, "none\n");
	} else {
		ret = sprintf(page, "unknown\n");
	}

	return ret;
}