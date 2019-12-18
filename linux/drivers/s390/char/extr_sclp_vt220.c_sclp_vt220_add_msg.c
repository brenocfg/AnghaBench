#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {scalar_t__ length; } ;
struct sclp_vt220_sccb {TYPE_3__ evbuf; TYPE_2__ header; } ;
struct TYPE_4__ {scalar_t__ sccb; } ;
struct sclp_vt220_request {TYPE_1__ sclp_req; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int sclp_vt220_space_left (struct sclp_vt220_request*) ; 

__attribute__((used)) static int
sclp_vt220_add_msg(struct sclp_vt220_request *request,
		   const unsigned char *msg, int count, int convertlf)
{
	struct sclp_vt220_sccb *sccb;
	void *buffer;
	unsigned char c;
	int from;
	int to;

	if (count > sclp_vt220_space_left(request))
		count = sclp_vt220_space_left(request);
	if (count <= 0)
		return 0;

	sccb = (struct sclp_vt220_sccb *) request->sclp_req.sccb;
	buffer = (void *) ((addr_t) sccb + sccb->header.length);

	if (convertlf) {
		/* Perform Linefeed conversion (0x0a -> 0x0a 0x0d)*/
		for (from=0, to=0;
		     (from < count) && (to < sclp_vt220_space_left(request));
		     from++) {
			/* Retrieve character */
			c = msg[from];
			/* Perform conversion */
			if (c == 0x0a) {
				if (to + 1 < sclp_vt220_space_left(request)) {
					((unsigned char *) buffer)[to++] = c;
					((unsigned char *) buffer)[to++] = 0x0d;
				} else
					break;

			} else
				((unsigned char *) buffer)[to++] = c;
		}
		sccb->header.length += to;
		sccb->evbuf.length += to;
		return from;
	} else {
		memcpy(buffer, (const void *) msg, count);
		sccb->header.length += count;
		sccb->evbuf.length += count;
		return count;
	}
}