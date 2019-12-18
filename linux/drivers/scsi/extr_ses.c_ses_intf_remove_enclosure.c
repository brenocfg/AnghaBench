#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ses_device {struct ses_device* page2; struct ses_device* page1; struct ses_device* page10; } ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct enclosure_device {int /*<<< orphan*/  edev; TYPE_1__* component; struct ses_device* scratch; } ;
struct TYPE_2__ {struct ses_device* scratch; } ;

/* Variables and functions */
 struct enclosure_device* enclosure_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enclosure_unregister (struct enclosure_device*) ; 
 int /*<<< orphan*/  kfree (struct ses_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ses_intf_remove_enclosure(struct scsi_device *sdev)
{
	struct enclosure_device *edev;
	struct ses_device *ses_dev;

	/*  exact match to this enclosure */
	edev = enclosure_find(&sdev->sdev_gendev, NULL);
	if (!edev)
		return;

	ses_dev = edev->scratch;
	edev->scratch = NULL;

	kfree(ses_dev->page10);
	kfree(ses_dev->page1);
	kfree(ses_dev->page2);
	kfree(ses_dev);

	kfree(edev->component[0].scratch);

	put_device(&edev->edev);
	enclosure_unregister(edev);
}