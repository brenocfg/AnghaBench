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
struct zfcp_scsi_dev {TYPE_1__* port; } ;
struct scsi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_erp_lun_shutdown_wait (struct scsi_device*,char*) ; 

__attribute__((used)) static void zfcp_scsi_slave_destroy(struct scsi_device *sdev)
{
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	/* if previous slave_alloc returned early, there is nothing to do */
	if (!zfcp_sdev->port)
		return;

	zfcp_erp_lun_shutdown_wait(sdev, "scssd_1");
	put_device(&zfcp_sdev->port->dev);
}