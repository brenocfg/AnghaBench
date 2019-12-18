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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sdev_store_timeout (struct device *dev, struct device_attribute *attr,
		    const char *buf, size_t count)
{
	struct scsi_device *sdev;
	int timeout;
	sdev = to_scsi_device(dev);
	sscanf (buf, "%d\n", &timeout);
	blk_queue_rq_timeout(sdev->request_queue, timeout * HZ);
	return count;
}