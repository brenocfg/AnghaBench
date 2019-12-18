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
struct tape_request {int dummy; } ;
struct tape_device {TYPE_1__* cdev; } ;
struct irb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int tape_3590_erp_basic (struct tape_device*,struct tape_request*,struct irb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tape_3590_erp_swap(struct tape_device *device, struct tape_request *request,
		   struct irb *irb)
{
	/*
	 * This error recovery should swap the tapes
	 * if the original has a problem. The operation
	 * should proceed with the new tape... this
	 * should probably be done in user space!
	 */
	dev_warn (&device->cdev->dev, "The tape medium must be loaded into a "
		"different tape unit\n");
	return tape_3590_erp_basic(device, request, irb, -EIO);
}