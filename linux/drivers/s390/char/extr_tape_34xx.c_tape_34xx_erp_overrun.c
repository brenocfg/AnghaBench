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
struct irb {int* ecw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int tape_34xx_erp_bug (struct tape_device*,struct tape_request*,struct irb*,int) ; 
 int tape_34xx_erp_failed (struct tape_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tape_34xx_erp_overrun(struct tape_device *device, struct tape_request *request,
		      struct irb *irb)
{
	if (irb->ecw[3] == 0x40) {
		dev_warn (&device->cdev->dev, "A data overrun occurred between"
			" the control unit and tape unit\n");
		return tape_34xx_erp_failed(request, -EIO);
	}
	return tape_34xx_erp_bug(device, request, irb, -1);
}