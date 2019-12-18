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
struct pvr2_buffer {int /*<<< orphan*/  purb; int /*<<< orphan*/ * stream; scalar_t__ signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_BUF_POOL ; 
 int /*<<< orphan*/  pvr2_buffer_describe (struct pvr2_buffer*,char*) ; 
 int /*<<< orphan*/  pvr2_buffer_set_none (struct pvr2_buffer*) ; 
 int /*<<< orphan*/  pvr2_buffer_wipe (struct pvr2_buffer*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_buffer*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvr2_buffer_done(struct pvr2_buffer *bp)
{
#ifdef SANITY_CHECK_BUFFERS
	pvr2_buffer_describe(bp, "delete");
#endif
	pvr2_buffer_wipe(bp);
	pvr2_buffer_set_none(bp);
	bp->signature = 0;
	bp->stream = NULL;
	usb_free_urb(bp->purb);
	pvr2_trace(PVR2_TRACE_BUF_POOL, "/*---TRACE_FLOW---*/ bufferDone     %p",
		   bp);
}