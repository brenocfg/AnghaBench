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
struct status_block {int status_idx; } ;
struct cnic_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int cnic_service_bnx2_queues (struct cnic_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cnic_service_bnx2(void *data, void *status_blk)
{
	struct cnic_dev *dev = data;

	if (unlikely(!test_bit(CNIC_F_CNIC_UP, &dev->flags))) {
		struct status_block *sblk = status_blk;

		return sblk->status_idx;
	}

	return cnic_service_bnx2_queues(dev);
}