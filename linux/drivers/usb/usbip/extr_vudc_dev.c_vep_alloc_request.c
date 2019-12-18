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
struct usb_request {int dummy; } ;
struct vrequest {struct usb_request req; int /*<<< orphan*/  req_entry; } ;
struct usb_ep {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct vrequest* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_request *vep_alloc_request(struct usb_ep *_ep,
		gfp_t mem_flags)
{
	struct vrequest *req;

	if (!_ep)
		return NULL;

	req = kzalloc(sizeof(*req), mem_flags);
	if (!req)
		return NULL;

	INIT_LIST_HEAD(&req->req_entry);

	return &req->req;
}