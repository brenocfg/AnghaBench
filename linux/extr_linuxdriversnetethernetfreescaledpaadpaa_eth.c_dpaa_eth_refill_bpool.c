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
struct dpaa_bp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FSL_DPAA_ETH_MAX_BUF_COUNT ; 
 int FSL_DPAA_ETH_REFILL_THRESHOLD ; 
 int dpaa_bp_add_8_bufs (struct dpaa_bp*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dpaa_eth_refill_bpool(struct dpaa_bp *dpaa_bp, int *countptr)
{
	int count = *countptr;
	int new_bufs;

	if (unlikely(count < FSL_DPAA_ETH_REFILL_THRESHOLD)) {
		do {
			new_bufs = dpaa_bp_add_8_bufs(dpaa_bp);
			if (unlikely(!new_bufs)) {
				/* Avoid looping forever if we've temporarily
				 * run out of memory. We'll try again at the
				 * next NAPI cycle.
				 */
				break;
			}
			count += new_bufs;
		} while (count < FSL_DPAA_ETH_MAX_BUF_COUNT);

		*countptr = count;
		if (unlikely(count < FSL_DPAA_ETH_MAX_BUF_COUNT))
			return -ENOMEM;
	}

	return 0;
}