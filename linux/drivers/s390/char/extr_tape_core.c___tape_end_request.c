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
struct tape_request {int rc; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (struct tape_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  list; int /*<<< orphan*/  status; } ;
struct tape_device {int /*<<< orphan*/  req_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*,struct tape_device*,struct tape_request*,int) ; 
 int /*<<< orphan*/  TAPE_REQUEST_DONE ; 
 int /*<<< orphan*/  __tape_start_next_request (struct tape_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tape_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__tape_end_request(
	struct tape_device *	device,
	struct tape_request *	request,
	int			rc)
{
	DBF_LH(6, "__tape_end_request(%p, %p, %i)\n", device, request, rc);
	if (request) {
		request->rc = rc;
		request->status = TAPE_REQUEST_DONE;

		/* Remove from request queue. */
		list_del(&request->list);

		/* Do callback. */
		if (request->callback != NULL)
			request->callback(request, request->callback_data);
	}

	/* Start next request. */
	if (!list_empty(&device->req_queue))
		__tape_start_next_request(device);
}