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
struct inbuf_t {scalar_t__ head; scalar_t__ tail; int inputstate; struct cardstate* cs; } ;
struct cardstate {scalar_t__ mstate; TYPE_1__* bcs; } ;
struct TYPE_2__ {scalar_t__ proto2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INTR ; 
 int INS_command ; 
 scalar_t__ L2_HDLC ; 
 scalar_t__ MS_LOCKED ; 
 unsigned int RBUFSIZE ; 
 unsigned int cmd_loop (unsigned int,struct inbuf_t*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  handle_dle (struct inbuf_t*) ; 
 unsigned int hdlc_loop (unsigned int,struct inbuf_t*) ; 
 unsigned int iraw_loop (unsigned int,struct inbuf_t*) ; 
 unsigned int lock_loop (unsigned int,struct inbuf_t*) ; 

void gigaset_m10x_input(struct inbuf_t *inbuf)
{
	struct cardstate *cs = inbuf->cs;
	unsigned numbytes, procbytes;

	gig_dbg(DEBUG_INTR, "buffer state: %u -> %u", inbuf->head, inbuf->tail);

	while (inbuf->head != inbuf->tail) {
		/* check for DLE escape */
		handle_dle(inbuf);

		/* process a contiguous block of bytes */
		numbytes = (inbuf->head > inbuf->tail ?
			    RBUFSIZE : inbuf->tail) - inbuf->head;
		gig_dbg(DEBUG_INTR, "processing %u bytes", numbytes);
		/*
		 * numbytes may be 0 if handle_dle() ate the last byte.
		 * This does no harm, *_loop() will just return 0 immediately.
		 */

		if (cs->mstate == MS_LOCKED)
			procbytes = lock_loop(numbytes, inbuf);
		else if (inbuf->inputstate & INS_command)
			procbytes = cmd_loop(numbytes, inbuf);
		else if (cs->bcs->proto2 == L2_HDLC)
			procbytes = hdlc_loop(numbytes, inbuf);
		else
			procbytes = iraw_loop(numbytes, inbuf);
		inbuf->head += procbytes;

		/* check for buffer wraparound */
		if (inbuf->head >= RBUFSIZE)
			inbuf->head = 0;

		gig_dbg(DEBUG_INTR, "head set to %u", inbuf->head);
	}
}