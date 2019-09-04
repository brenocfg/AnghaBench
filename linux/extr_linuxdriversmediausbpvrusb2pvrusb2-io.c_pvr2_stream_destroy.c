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
struct pvr2_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 int /*<<< orphan*/  kfree (struct pvr2_stream*) ; 
 int /*<<< orphan*/  pvr2_stream_done (struct pvr2_stream*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_stream*) ; 

void pvr2_stream_destroy(struct pvr2_stream *sp)
{
	if (!sp) return;
	pvr2_trace(PVR2_TRACE_INIT, "pvr2_stream_destroy: sp=%p", sp);
	pvr2_stream_done(sp);
	kfree(sp);
}