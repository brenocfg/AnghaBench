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
struct mapped_device {int /*<<< orphan*/  flags; int /*<<< orphan*/ * frozen_sb; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_FROZEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * freeze_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lock_fs(struct mapped_device *md)
{
	int r;

	WARN_ON(md->frozen_sb);

	md->frozen_sb = freeze_bdev(md->bdev);
	if (IS_ERR(md->frozen_sb)) {
		r = PTR_ERR(md->frozen_sb);
		md->frozen_sb = NULL;
		return r;
	}

	set_bit(DMF_FROZEN, &md->flags);

	return 0;
}