#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stripe_head {int disks; int /*<<< orphan*/  state; int /*<<< orphan*/  sector; TYPE_2__* dev; } ;
struct r5conf {TYPE_1__* mddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; scalar_t__ written; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  STRIPE_DEGRADED ; 
 int /*<<< orphan*/  STRIPE_SECTORS ; 
 int /*<<< orphan*/  md_bitmap_endwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5c_return_dev_pending_writes (struct r5conf*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void r5c_handle_cached_data_endio(struct r5conf *conf,
				  struct stripe_head *sh, int disks)
{
	int i;

	for (i = sh->disks; i--; ) {
		if (sh->dev[i].written) {
			set_bit(R5_UPTODATE, &sh->dev[i].flags);
			r5c_return_dev_pending_writes(conf, &sh->dev[i]);
			md_bitmap_endwrite(conf->mddev->bitmap, sh->sector,
					   STRIPE_SECTORS,
					   !test_bit(STRIPE_DEGRADED, &sh->state),
					   0);
		}
	}
}