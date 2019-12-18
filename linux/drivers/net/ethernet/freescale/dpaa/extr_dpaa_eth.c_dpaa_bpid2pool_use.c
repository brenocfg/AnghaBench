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
struct TYPE_2__ {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 TYPE_1__** dpaa_bp_array ; 
 scalar_t__ dpaa_bpid2pool (int) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dpaa_bpid2pool_use(int bpid)
{
	if (dpaa_bpid2pool(bpid)) {
		refcount_inc(&dpaa_bp_array[bpid]->refs);
		return true;
	}

	return false;
}