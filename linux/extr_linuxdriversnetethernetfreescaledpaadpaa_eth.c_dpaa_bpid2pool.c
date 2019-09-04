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
 int BM_MAX_NUM_OF_POOLS ; 
 scalar_t__ WARN_ON (int) ; 
 struct dpaa_bp** dpaa_bp_array ; 

__attribute__((used)) static struct dpaa_bp *dpaa_bpid2pool(int bpid)
{
	if (WARN_ON(bpid < 0 || bpid >= BM_MAX_NUM_OF_POOLS))
		return NULL;

	return dpaa_bp_array[bpid];
}