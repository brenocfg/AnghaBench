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
struct rxe_dev {int /*<<< orphan*/  usdev_lock; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  mmap_offset_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxe_cleanup_ports (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_init_device_param (struct rxe_dev*) ; 
 int rxe_init_pools (struct rxe_dev*) ; 
 int rxe_init_ports (struct rxe_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxe_init(struct rxe_dev *rxe)
{
	int err;

	/* init default device parameters */
	rxe_init_device_param(rxe);

	err = rxe_init_ports(rxe);
	if (err)
		goto err1;

	err = rxe_init_pools(rxe);
	if (err)
		goto err2;

	/* init pending mmap list */
	spin_lock_init(&rxe->mmap_offset_lock);
	spin_lock_init(&rxe->pending_lock);
	INIT_LIST_HEAD(&rxe->pending_mmaps);

	mutex_init(&rxe->usdev_lock);

	return 0;

err2:
	rxe_cleanup_ports(rxe);
err1:
	return err;
}