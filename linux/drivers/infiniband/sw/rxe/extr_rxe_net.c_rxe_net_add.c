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
struct rxe_dev {int /*<<< orphan*/  ib_dev; struct net_device* ndev; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct rxe_dev* ib_alloc_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dev ; 
 int rxe_add (struct rxe_dev*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rxe_dev ; 

int rxe_net_add(const char *ibdev_name, struct net_device *ndev)
{
	int err;
	struct rxe_dev *rxe = NULL;

	rxe = ib_alloc_device(rxe_dev, ib_dev);
	if (!rxe)
		return -ENOMEM;

	rxe->ndev = ndev;

	err = rxe_add(rxe, ndev->mtu, ibdev_name);
	if (err) {
		ib_dealloc_device(&rxe->ib_dev);
		return err;
	}

	return 0;
}