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
struct scif_peer_dev {int /*<<< orphan*/  dev; } ;
struct scif_dev {int /*<<< orphan*/  spdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device* get_device (int /*<<< orphan*/ *) ; 
 struct scif_peer_dev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline struct device *scif_get_peer_dev(struct scif_dev *scifdev)
{
	struct scif_peer_dev *spdev;
	struct device *spdev_ret;

	rcu_read_lock();
	spdev = rcu_dereference(scifdev->spdev);
	if (spdev)
		spdev_ret = get_device(&spdev->dev);
	else
		spdev_ret = ERR_PTR(-ENODEV);
	rcu_read_unlock();
	return spdev_ret;
}