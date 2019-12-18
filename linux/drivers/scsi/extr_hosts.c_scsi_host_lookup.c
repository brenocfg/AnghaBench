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
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __scsi_host_match ; 
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct Scsi_Host* scsi_host_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_class ; 

struct Scsi_Host *scsi_host_lookup(unsigned short hostnum)
{
	struct device *cdev;
	struct Scsi_Host *shost = NULL;

	cdev = class_find_device(&shost_class, NULL, &hostnum,
				 __scsi_host_match);
	if (cdev) {
		shost = scsi_host_get(class_to_shost(cdev));
		put_device(cdev);
	}
	return shost;
}