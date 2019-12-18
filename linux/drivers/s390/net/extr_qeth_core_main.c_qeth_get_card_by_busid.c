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
struct qeth_card {int dummy; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct ccwgroup_device* get_ccwgroupdev_by_busid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_core_ccwgroup_driver ; 

struct qeth_card *qeth_get_card_by_busid(char *bus_id)
{
	struct ccwgroup_device *gdev;
	struct qeth_card *card;

	gdev = get_ccwgroupdev_by_busid(&qeth_core_ccwgroup_driver, bus_id);
	if (!gdev)
		return NULL;

	card = dev_get_drvdata(&gdev->dev);
	put_device(&gdev->dev);
	return card;
}