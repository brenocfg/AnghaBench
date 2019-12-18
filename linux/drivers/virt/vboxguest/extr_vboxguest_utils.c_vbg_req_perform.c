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
struct vmmdev_request_header {int rc; } ;
struct vbg_dev {scalar_t__ io_port; } ;

/* Variables and functions */
 scalar_t__ VMMDEV_PORT_OFF_REQUEST ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  outl (unsigned long,scalar_t__) ; 
 unsigned long virt_to_phys (void*) ; 

int vbg_req_perform(struct vbg_dev *gdev, void *req)
{
	unsigned long phys_req = virt_to_phys(req);

	outl(phys_req, gdev->io_port + VMMDEV_PORT_OFF_REQUEST);
	/*
	 * The host changes the request as a result of the outl, make sure
	 * the outl and any reads of the req happen in the correct order.
	 */
	mb();

	return ((struct vmmdev_request_header *)req)->rc;
}