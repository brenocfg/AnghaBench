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
struct r10bio {int /*<<< orphan*/  state; } ;
struct md_rdev {int /*<<< orphan*/  new_data_offset; int /*<<< orphan*/  data_offset; TYPE_1__* mddev; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  recovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_RESHAPE ; 
 int /*<<< orphan*/  R10BIO_Previous ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sector_t choose_data_offset(struct r10bio *r10_bio,
				   struct md_rdev *rdev)
{
	if (!test_bit(MD_RECOVERY_RESHAPE, &rdev->mddev->recovery) ||
	    test_bit(R10BIO_Previous, &r10_bio->state))
		return rdev->data_offset;
	else
		return rdev->new_data_offset;
}