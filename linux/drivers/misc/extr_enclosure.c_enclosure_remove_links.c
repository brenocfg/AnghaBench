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
struct TYPE_6__ {scalar_t__ sd; } ;
struct TYPE_5__ {TYPE_3__ kobj; } ;
struct enclosure_component {TYPE_2__ cdev; TYPE_1__* dev; } ;
struct TYPE_4__ {TYPE_3__ kobj; } ;

/* Variables and functions */
 int ENCLOSURE_NAME_SIZE ; 
 int /*<<< orphan*/  enclosure_link_name (struct enclosure_component*,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (TYPE_3__*,char*) ; 

__attribute__((used)) static void enclosure_remove_links(struct enclosure_component *cdev)
{
	char name[ENCLOSURE_NAME_SIZE];

	enclosure_link_name(cdev, name);

	/*
	 * In odd circumstances, like multipath devices, something else may
	 * already have removed the links, so check for this condition first.
	 */
	if (cdev->dev->kobj.sd)
		sysfs_remove_link(&cdev->dev->kobj, name);

	if (cdev->cdev.kobj.sd)
		sysfs_remove_link(&cdev->cdev.kobj, "device");
}