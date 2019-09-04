#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kset; } ;
struct edd_device {TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  edd_dev_set_info (struct edd_device*,int) ; 
 int /*<<< orphan*/  edd_kset ; 
 int /*<<< orphan*/  edd_ktype ; 
 int /*<<< orphan*/  edd_populate_dir (struct edd_device*) ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_uevent (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
edd_device_register(struct edd_device *edev, int i)
{
	int error;

	if (!edev)
		return 1;
	edd_dev_set_info(edev, i);
	edev->kobj.kset = edd_kset;
	error = kobject_init_and_add(&edev->kobj, &edd_ktype, NULL,
				     "int13_dev%02x", 0x80 + i);
	if (!error) {
		edd_populate_dir(edev);
		kobject_uevent(&edev->kobj, KOBJ_ADD);
	}
	return error;
}