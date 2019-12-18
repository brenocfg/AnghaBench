#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int response_code; } ;
struct sclp_vt220_sccb {TYPE_1__ header; } ;
struct TYPE_4__ {void* status; scalar_t__ sccb; } ;
struct sclp_vt220_request {TYPE_2__ sclp_req; int /*<<< orphan*/  retry_count; } ;
struct sclp_req {scalar_t__ status; } ;
struct sccb_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCLP_BUFFER_MAX_RETRY ; 
 scalar_t__ SCLP_REQ_FAILED ; 
 void* SCLP_REQ_FILLED ; 
 int /*<<< orphan*/  sclp_add_request (struct sclp_req*) ; 
 int /*<<< orphan*/  sclp_remove_processed (struct sccb_header*) ; 
 int /*<<< orphan*/  sclp_vt220_process_queue (struct sclp_vt220_request*) ; 

__attribute__((used)) static void
sclp_vt220_callback(struct sclp_req *request, void *data)
{
	struct sclp_vt220_request *vt220_request;
	struct sclp_vt220_sccb *sccb;

	vt220_request = (struct sclp_vt220_request *) data;
	if (request->status == SCLP_REQ_FAILED) {
		sclp_vt220_process_queue(vt220_request);
		return;
	}
	sccb = (struct sclp_vt220_sccb *) vt220_request->sclp_req.sccb;

	/* Check SCLP response code and choose suitable action	*/
	switch (sccb->header.response_code) {
	case 0x0020 :
		break;

	case 0x05f0: /* Target resource in improper state */
		break;

	case 0x0340: /* Contained SCLP equipment check */
		if (++vt220_request->retry_count > SCLP_BUFFER_MAX_RETRY)
			break;
		/* Remove processed buffers and requeue rest */
		if (sclp_remove_processed((struct sccb_header *) sccb) > 0) {
			/* Not all buffers were processed */
			sccb->header.response_code = 0x0000;
			vt220_request->sclp_req.status = SCLP_REQ_FILLED;
			if (sclp_add_request(request) == 0)
				return;
		}
		break;

	case 0x0040: /* SCLP equipment check */
		if (++vt220_request->retry_count > SCLP_BUFFER_MAX_RETRY)
			break;
		sccb->header.response_code = 0x0000;
		vt220_request->sclp_req.status = SCLP_REQ_FILLED;
		if (sclp_add_request(request) == 0)
			return;
		break;

	default:
		break;
	}
	sclp_vt220_process_queue(vt220_request);
}