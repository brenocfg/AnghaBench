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
struct hfi1_devdata {int unit; int /*<<< orphan*/  kobj; int /*<<< orphan*/  user_device; int /*<<< orphan*/  user_cdev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 char* class_name () ; 
 int hfi1_cdev_init (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_file_ops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  user_remove (struct hfi1_devdata*) ; 

__attribute__((used)) static int user_add(struct hfi1_devdata *dd)
{
	char name[10];
	int ret;

	snprintf(name, sizeof(name), "%s_%d", class_name(), dd->unit);
	ret = hfi1_cdev_init(dd->unit, name, &hfi1_file_ops,
			     &dd->user_cdev, &dd->user_device,
			     true, &dd->kobj);
	if (ret)
		user_remove(dd);

	return ret;
}