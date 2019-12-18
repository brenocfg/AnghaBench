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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {unsigned int supported_mode; } ;

/* Variables and functions */
 unsigned int MODE_INITIATOR ; 
 unsigned int MODE_UNKNOWN ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  show_shost_mode (unsigned int,char*) ; 

__attribute__((used)) static ssize_t
show_shost_supported_mode(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	unsigned int supported_mode = shost->hostt->supported_mode;

	if (supported_mode == MODE_UNKNOWN)
		/* by default this should be initiator */
		supported_mode = MODE_INITIATOR;

	return show_shost_mode(supported_mode, buf);
}