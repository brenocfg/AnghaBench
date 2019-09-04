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
struct scif_peer_dev {int dummy; } ;
struct scif_dev {int /*<<< orphan*/  spdev; } ;

/* Variables and functions */
 struct scif_peer_dev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline int _scifdev_alive(struct scif_dev *scifdev)
{
	struct scif_peer_dev *spdev;

	rcu_read_lock();
	spdev = rcu_dereference(scifdev->spdev);
	rcu_read_unlock();
	return !!spdev;
}