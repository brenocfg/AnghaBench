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
typedef  int u32 ;
struct hfi1_devdata {TYPE_1__** rcd; } ;
struct TYPE_2__ {int rcvhdrqentsize; } ;

/* Variables and functions */

u32 lrh_max_header_bytes(struct hfi1_devdata *dd)
{
	/*
	 * The maximum non-payload (MTU) bytes in LRH.PktLen are
	 * the Receive Header Entry Size minus the PBC (or RHF) size
	 * plus one DW for the ICRC appended by HW.
	 *
	 * dd->rcd[0].rcvhdrqentsize is in DW.
	 * We use rcd[0] as all context will have the same value. Also,
	 * the first kernel context would have been allocated by now so
	 * we are guaranteed a valid value.
	 */
	return (dd->rcd[0]->rcvhdrqentsize - 2/*PBC/RHF*/ + 1/*ICRC*/) << 2;
}