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
struct scsi_target {int dummy; } ;
struct device {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct scsi_target*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct scsi_target* to_scsi_target (struct device*) ; 

__attribute__((used)) static void scsi_target_dev_release(struct device *dev)
{
	struct device *parent = dev->parent;
	struct scsi_target *starget = to_scsi_target(dev);

	kfree(starget);
	put_device(parent);
}