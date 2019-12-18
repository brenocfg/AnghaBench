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
struct dpaa_bp {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 struct dpaa_bp** dpaa_bp_array ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void dpaa_bpid2pool_map(int bpid, struct dpaa_bp *dpaa_bp)
{
	dpaa_bp_array[bpid] = dpaa_bp;
	refcount_set(&dpaa_bp->refs, 1);
}