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
struct qib_devdata {int unit; int /*<<< orphan*/  user_device; int /*<<< orphan*/  user_cdev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int qib_cdev_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_file_ops ; 
 int /*<<< orphan*/  qib_user_remove (struct qib_devdata*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  user_count ; 
 int /*<<< orphan*/  wildcard_cdev ; 
 int /*<<< orphan*/  wildcard_device ; 

__attribute__((used)) static int qib_user_add(struct qib_devdata *dd)
{
	char name[10];
	int ret;

	if (atomic_inc_return(&user_count) == 1) {
		ret = qib_cdev_init(0, "ipath", &qib_file_ops,
				    &wildcard_cdev, &wildcard_device);
		if (ret)
			goto done;
	}

	snprintf(name, sizeof(name), "ipath%d", dd->unit);
	ret = qib_cdev_init(dd->unit + 1, name, &qib_file_ops,
			    &dd->user_cdev, &dd->user_device);
	if (ret)
		qib_user_remove(dd);
done:
	return ret;
}