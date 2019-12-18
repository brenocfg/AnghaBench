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
struct hwa742_request {void (* complete ) (void*) ;void* complete_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_req (struct hwa742_request*) ; 
 int /*<<< orphan*/  process_pending_requests () ; 

__attribute__((used)) static void request_complete(void *data)
{
	struct hwa742_request	*req = (struct hwa742_request *)data;
	void			(*complete)(void *);
	void			*complete_data;

	complete = req->complete;
	complete_data = req->complete_data;

	free_req(req);

	if (complete)
		complete(complete_data);

	process_pending_requests();
}