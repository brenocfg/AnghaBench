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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct pedit_headers {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ __PEDIT_HDR_TYPE_MAX ; 
 int pedit_header (struct pedit_headers*,scalar_t__) ; 

__attribute__((used)) static int set_pedit_val(u8 hdr_type, u32 mask, u32 val, u32 offset,
			 struct pedit_headers *masks,
			 struct pedit_headers *vals)
{
	u32 *curr_pmask, *curr_pval;

	if (hdr_type >= __PEDIT_HDR_TYPE_MAX)
		goto out_err;

	curr_pmask = (u32 *)(pedit_header(masks, hdr_type) + offset);
	curr_pval  = (u32 *)(pedit_header(vals, hdr_type) + offset);

	if (*curr_pmask & mask)  /* disallow acting twice on the same location */
		goto out_err;

	*curr_pmask |= mask;
	*curr_pval  |= (val & mask);

	return 0;

out_err:
	return -EOPNOTSUPP;
}