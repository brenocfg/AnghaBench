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
struct enic {int /*<<< orphan*/  netdev; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int enic_dev_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vnic_dev_hang_reset ; 
 int /*<<< orphan*/  vnic_dev_hang_reset_done ; 

__attribute__((used)) static int enic_dev_hang_reset(struct enic *enic)
{
	int err;

	err = enic_dev_wait(enic->vdev, vnic_dev_hang_reset,
		vnic_dev_hang_reset_done, 0);
	if (err)
		netdev_err(enic->netdev, "vNIC hang reset failed, err %d\n",
			err);

	return err;
}