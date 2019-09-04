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
struct pvrdma_dev {int /*<<< orphan*/  num_ahs; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_vah (struct ib_ah*) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 

int pvrdma_destroy_ah(struct ib_ah *ah)
{
	struct pvrdma_dev *dev = to_vdev(ah->device);

	kfree(to_vah(ah));
	atomic_dec(&dev->num_ahs);

	return 0;
}