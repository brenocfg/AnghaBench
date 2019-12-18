#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wacom_remote {TYPE_1__* remotes; int /*<<< orphan*/  remote_dir; } ;
struct wacom {TYPE_2__* hdev; struct wacom_remote* remote; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_3__ group; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __wacom_devm_sysfs_create_group (struct wacom*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (TYPE_2__*,char*,int) ; 

__attribute__((used)) static int wacom_remote_create_attr_group(struct wacom *wacom, __u32 serial,
					  int index)
{
	int error = 0;
	struct wacom_remote *remote = wacom->remote;

	remote->remotes[index].group.name = devm_kasprintf(&wacom->hdev->dev,
							  GFP_KERNEL,
							  "%d", serial);
	if (!remote->remotes[index].group.name)
		return -ENOMEM;

	error = __wacom_devm_sysfs_create_group(wacom, remote->remote_dir,
						&remote->remotes[index].group);
	if (error) {
		remote->remotes[index].group.name = NULL;
		hid_err(wacom->hdev,
			"cannot create sysfs group err: %d\n", error);
		return error;
	}

	return 0;
}