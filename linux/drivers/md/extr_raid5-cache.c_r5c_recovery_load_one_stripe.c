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
struct stripe_head {int disks; struct r5dev* dev; } ;
struct r5l_log {int dummy; } ;
struct r5dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  R5_Wantwrite ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r5c_recovery_load_one_stripe(struct r5l_log *log,
					 struct stripe_head *sh)
{
	struct r5dev *dev;
	int i;

	for (i = sh->disks; i--; ) {
		dev = sh->dev + i;
		if (test_and_clear_bit(R5_Wantwrite, &dev->flags)) {
			set_bit(R5_InJournal, &dev->flags);
			set_bit(R5_UPTODATE, &dev->flags);
		}
	}
}