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
struct usb_request {struct ffs_data* context; } ;
struct usb_ep {int dummy; } ;
struct ffs_data {int /*<<< orphan*/  ep0req_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffs_ep0_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct ffs_data *ffs = req->context;

	complete(&ffs->ep0req_completion);
}