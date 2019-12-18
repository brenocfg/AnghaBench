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
struct scsi_target {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  child_iter ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct scsi_target* transport_class_to_starget (struct device*) ; 

__attribute__((used)) static ssize_t
store_spi_revalidate(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	struct scsi_target *starget = transport_class_to_starget(dev);

	device_for_each_child(&starget->dev, NULL, child_iter);
	return count;
}