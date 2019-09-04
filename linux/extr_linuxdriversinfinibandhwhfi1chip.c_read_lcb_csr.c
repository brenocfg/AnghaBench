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
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_lcb_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_lcb_via_8051 (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int read_lcb_csr(struct hfi1_devdata *dd, u32 addr, u64 *data)
{
	struct hfi1_pportdata *ppd = dd->pport;

	/* if up, go through the 8051 for the value */
	if (ppd->host_link_state & HLS_UP)
		return read_lcb_via_8051(dd, addr, data);
	/* if going up or down, check the cache, otherwise, no access */
	if (ppd->host_link_state & (HLS_GOING_UP | HLS_GOING_OFFLINE)) {
		if (read_lcb_cache(addr, data))
			return -EBUSY;
		return 0;
	}

	/* otherwise, host has access */
	*data = read_csr(dd, addr);
	return 0;
}