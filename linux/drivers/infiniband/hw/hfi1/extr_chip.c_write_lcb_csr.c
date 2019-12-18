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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_pportdata {int host_link_state; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int EBUSY ; 
 int HLS_GOING_OFFLINE ; 
 int HLS_GOING_UP ; 
 int HLS_UP ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_lcb_via_8051 (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int write_lcb_csr(struct hfi1_devdata *dd, u32 addr, u64 data)
{
	struct hfi1_pportdata *ppd = dd->pport;

	/* if up, go through the 8051 for the value */
	if (ppd->host_link_state & HLS_UP)
		return write_lcb_via_8051(dd, addr, data);
	/* if going up or down, no access */
	if (ppd->host_link_state & (HLS_GOING_UP | HLS_GOING_OFFLINE))
		return -EBUSY;
	/* otherwise, host has access */
	write_csr(dd, addr, data);
	return 0;
}