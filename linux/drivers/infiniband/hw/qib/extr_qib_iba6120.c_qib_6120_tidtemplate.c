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
typedef  int u32 ;
struct qib_devdata {int rcvegrbufsize; unsigned int tidtemplate; scalar_t__ tidinvalid; } ;

/* Variables and functions */

__attribute__((used)) static void qib_6120_tidtemplate(struct qib_devdata *dd)
{
	u32 egrsize = dd->rcvegrbufsize;

	/*
	 * For now, we always allocate 4KB buffers (at init) so we can
	 * receive max size packets.  We may want a module parameter to
	 * specify 2KB or 4KB and/or make be per ctxt instead of per device
	 * for those who want to reduce memory footprint.  Note that the
	 * rcvhdrentsize size must be large enough to hold the largest
	 * IB header (currently 96 bytes) that we expect to handle (plus of
	 * course the 2 dwords of RHF).
	 */
	if (egrsize == 2048)
		dd->tidtemplate = 1U << 29;
	else if (egrsize == 4096)
		dd->tidtemplate = 2U << 29;
	dd->tidinvalid = 0;
}