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
struct TYPE_2__ {void* callback_data; int /*<<< orphan*/  callback; int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;
struct sclp_vt220_request {TYPE_1__ sclp_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_DATA ; 
 int /*<<< orphan*/  SCLP_REQ_FILLED ; 
 int sclp_add_request (TYPE_1__*) ; 
 int /*<<< orphan*/  sclp_vt220_callback ; 

__attribute__((used)) static int
__sclp_vt220_emit(struct sclp_vt220_request *request)
{
	request->sclp_req.command = SCLP_CMDW_WRITE_EVENT_DATA;
	request->sclp_req.status = SCLP_REQ_FILLED;
	request->sclp_req.callback = sclp_vt220_callback;
	request->sclp_req.callback_data = (void *) request;

	return sclp_add_request(&request->sclp_req);
}