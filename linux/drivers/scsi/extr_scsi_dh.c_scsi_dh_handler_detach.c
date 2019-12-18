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
struct scsi_device {TYPE_1__* handler; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; int /*<<< orphan*/  name; int /*<<< orphan*/  (* detach ) (struct scsi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_device*) ; 

__attribute__((used)) static void scsi_dh_handler_detach(struct scsi_device *sdev)
{
	sdev->handler->detach(sdev);
	sdev_printk(KERN_NOTICE, sdev, "%s: Detached\n", sdev->handler->name);
	module_put(sdev->handler->module);
}