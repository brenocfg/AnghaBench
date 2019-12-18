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
struct qib_devdata {int /*<<< orphan*/  user_device; int /*<<< orphan*/  user_cdev; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_cdev_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_count ; 
 int /*<<< orphan*/  wildcard_cdev ; 
 int /*<<< orphan*/  wildcard_device ; 

__attribute__((used)) static void qib_user_remove(struct qib_devdata *dd)
{
	if (atomic_dec_return(&user_count) == 0)
		qib_cdev_cleanup(&wildcard_cdev, &wildcard_device);

	qib_cdev_cleanup(&dd->user_cdev, &dd->user_device);
}