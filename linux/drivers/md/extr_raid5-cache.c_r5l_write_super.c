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
struct r5l_log {TYPE_1__* rdev; } ;
struct mddev {int /*<<< orphan*/  sb_flags; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  journal_tail; struct mddev* mddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r5l_write_super(struct r5l_log *log, sector_t cp)
{
	struct mddev *mddev = log->rdev->mddev;

	log->rdev->journal_tail = cp;
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
}