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
struct dasd_device {int /*<<< orphan*/  cdev; } ;
struct dasd_ccw_req {scalar_t__ block; int /*<<< orphan*/  status; struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_STOPPED_PENDING ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int HZ ; 
 int /*<<< orphan*/  dasd_block_set_timer (scalar_t__,int) ; 
 int /*<<< orphan*/  dasd_device_set_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_device_set_timer (struct dasd_device*,int) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void dasd_3990_erp_block_queue(struct dasd_ccw_req *erp, int expires)
{

	struct dasd_device *device = erp->startdev;
	unsigned long flags;

	DBF_DEV_EVENT(DBF_INFO, device,
		    "blocking request queue for %is", expires/HZ);

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	dasd_device_set_stop_bits(device, DASD_STOPPED_PENDING);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	erp->status = DASD_CQR_FILLED;
	if (erp->block)
		dasd_block_set_timer(erp->block, expires);
	else
		dasd_device_set_timer(device, expires);
}