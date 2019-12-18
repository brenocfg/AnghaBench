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
struct scsi_device {scalar_t__ simple_tags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_queue_type_field(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	const char *name = "none";

	if (sdev->simple_tags)
		name = "simple";

	return snprintf(buf, 20, "%s\n", name);
}