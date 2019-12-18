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
struct rxe_dev {int /*<<< orphan*/  ib_dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  ib_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct rxe_dev* rxe_get_dev_from_net (struct net_device*) ; 
 int rxe_net_add (char const*,struct net_device*) ; 

__attribute__((used)) static int rxe_newlink(const char *ibdev_name, struct net_device *ndev)
{
	struct rxe_dev *exists;
	int err = 0;

	exists = rxe_get_dev_from_net(ndev);
	if (exists) {
		ib_device_put(&exists->ib_dev);
		pr_err("already configured on %s\n", ndev->name);
		err = -EEXIST;
		goto err;
	}

	err = rxe_net_add(ibdev_name, ndev);
	if (err) {
		pr_err("failed to add %s\n", ndev->name);
		goto err;
	}
err:
	return err;
}