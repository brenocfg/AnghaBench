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
struct aac_dev {int /*<<< orphan*/  scan_mutex; int /*<<< orphan*/  scsi_host_ptr; scalar_t__ sa_firmware; } ;

/* Variables and functions */
 int aac_scan_safw_host (struct aac_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_scan_host (int /*<<< orphan*/ ) ; 

int aac_scan_host(struct aac_dev *dev)
{
	int rcode = 0;

	mutex_lock(&dev->scan_mutex);
	if (dev->sa_firmware)
		rcode = aac_scan_safw_host(dev);
	else
		scsi_scan_host(dev->scsi_host_ptr);
	mutex_unlock(&dev->scan_mutex);

	return rcode;
}