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
typedef  int /*<<< orphan*/  u8 ;
struct rxe_dev {struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct rxe_dev* to_rdev (struct ib_device*) ; 

__attribute__((used)) static struct net_device *rxe_get_netdev(struct ib_device *device,
					 u8 port_num)
{
	struct rxe_dev *rxe = to_rdev(device);

	if (rxe->ndev) {
		dev_hold(rxe->ndev);
		return rxe->ndev;
	}

	return NULL;
}