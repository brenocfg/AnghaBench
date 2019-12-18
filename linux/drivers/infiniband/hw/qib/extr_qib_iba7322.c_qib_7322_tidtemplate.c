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
struct qib_devdata {int rcvegrbufsize; scalar_t__ tidinvalid; int /*<<< orphan*/  tidtemplate; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBA7322_TID_SZ_2K ; 
 int /*<<< orphan*/  IBA7322_TID_SZ_4K ; 

__attribute__((used)) static void qib_7322_tidtemplate(struct qib_devdata *dd)
{
	/*
	 * For now, we always allocate 4KB buffers (at init) so we can
	 * receive max size packets.  We may want a module parameter to
	 * specify 2KB or 4KB and/or make it per port instead of per device
	 * for those who want to reduce memory footprint.  Note that the
	 * rcvhdrentsize size must be large enough to hold the largest
	 * IB header (currently 96 bytes) that we expect to handle (plus of
	 * course the 2 dwords of RHF).
	 */
	if (dd->rcvegrbufsize == 2048)
		dd->tidtemplate = IBA7322_TID_SZ_2K;
	else if (dd->rcvegrbufsize == 4096)
		dd->tidtemplate = IBA7322_TID_SZ_4K;
	dd->tidinvalid = 0;
}