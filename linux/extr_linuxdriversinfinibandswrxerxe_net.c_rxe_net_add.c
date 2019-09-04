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
struct rxe_dev {int /*<<< orphan*/  list; int /*<<< orphan*/  ib_dev; struct net_device* ndev; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_list_lock ; 
 scalar_t__ ib_alloc_device (int) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rxe_add (struct rxe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_dev_list ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct rxe_dev *rxe_net_add(struct net_device *ndev)
{
	int err;
	struct rxe_dev *rxe = NULL;

	rxe = (struct rxe_dev *)ib_alloc_device(sizeof(*rxe));
	if (!rxe)
		return NULL;

	rxe->ndev = ndev;

	err = rxe_add(rxe, ndev->mtu);
	if (err) {
		ib_dealloc_device(&rxe->ib_dev);
		return NULL;
	}

	spin_lock_bh(&dev_list_lock);
	list_add_tail(&rxe->list, &rxe_dev_list);
	spin_unlock_bh(&dev_list_lock);
	return rxe;
}