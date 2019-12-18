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
struct scsi_device {int /*<<< orphan*/  sdev_gendev; TYPE_1__* handler; } ;
struct request_queue {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scsi_device* scsi_device_from_queue (struct request_queue*) ; 

const char *scsi_dh_attached_handler_name(struct request_queue *q, gfp_t gfp)
{
	struct scsi_device *sdev;
	const char *handler_name = NULL;

	sdev = scsi_device_from_queue(q);
	if (!sdev)
		return NULL;

	if (sdev->handler)
		handler_name = kstrdup(sdev->handler->name, gfp);
	put_device(&sdev->sdev_gendev);
	return handler_name;
}