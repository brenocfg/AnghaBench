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
struct net_device {int dummy; } ;
struct bnxt_re_dev {struct net_device* netdev; struct bnxt_en_dev* en_dev; } ;
struct bnxt_en_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_re_dev_remove (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_dev_unprobe (struct net_device*,struct bnxt_en_dev*) ; 

__attribute__((used)) static void bnxt_re_dev_unreg(struct bnxt_re_dev *rdev)
{
	struct bnxt_en_dev *en_dev = rdev->en_dev;
	struct net_device *netdev = rdev->netdev;

	bnxt_re_dev_remove(rdev);

	if (netdev)
		bnxt_re_dev_unprobe(netdev, en_dev);
}