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
struct timer_list {int dummy; } ;
struct tape_request {struct tape_device* device; } ;
struct tape_device {int /*<<< orphan*/  cdev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ,...) ; 
 struct tape_request* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct tape_request* request ; 
 int tape_cancel_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void
tape_std_assign_timeout(struct timer_list *t)
{
	struct tape_request *	request = from_timer(request, t, timer);
	struct tape_device *	device = request->device;
	int rc;

	BUG_ON(!device);

	DBF_EVENT(3, "%08x: Assignment timeout. Device busy.\n",
			device->cdev_id);
	rc = tape_cancel_io(device, request);
	if(rc)
		DBF_EVENT(3, "(%08x): Assign timeout: Cancel failed with rc = "
			  "%i\n", device->cdev_id, rc);
}