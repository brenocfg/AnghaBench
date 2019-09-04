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
struct mddev {int /*<<< orphan*/ * pers; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 struct md_rdev* md_find_rdev_rcu (struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_disk_faulty(struct mddev *mddev, dev_t dev)
{
	struct md_rdev *rdev;
	int err = 0;

	if (mddev->pers == NULL)
		return -ENODEV;

	rcu_read_lock();
	rdev = md_find_rdev_rcu(mddev, dev);
	if (!rdev)
		err =  -ENODEV;
	else {
		md_error(mddev, rdev);
		if (!test_bit(Faulty, &rdev->flags))
			err = -EBUSY;
	}
	rcu_read_unlock();
	return err;
}