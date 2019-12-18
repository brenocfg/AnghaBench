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
struct hfi1_pportdata {TYPE_1__* vl_arb_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int MAX_PRIO_TABLE ; 
 scalar_t__ VL_ARB_HIGH_PRIO_TABLE_SIZE ; 
 scalar_t__ VL_ARB_LOW_PRIO_TABLE_SIZE ; 
 scalar_t__ VL_ARB_TABLE_SIZE ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_vl_arb_caches(struct hfi1_pportdata *ppd)
{
	int i;

	BUILD_BUG_ON(VL_ARB_TABLE_SIZE !=
			VL_ARB_LOW_PRIO_TABLE_SIZE);
	BUILD_BUG_ON(VL_ARB_TABLE_SIZE !=
			VL_ARB_HIGH_PRIO_TABLE_SIZE);

	/*
	 * Note that we always return values directly from the
	 * 'vl_arb_cache' (and do no CSR reads) in response to a
	 * 'Get(VLArbTable)'. This is obviously correct after a
	 * 'Set(VLArbTable)', since the cache will then be up to
	 * date. But it's also correct prior to any 'Set(VLArbTable)'
	 * since then both the cache, and the relevant h/w registers
	 * will be zeroed.
	 */

	for (i = 0; i < MAX_PRIO_TABLE; i++)
		spin_lock_init(&ppd->vl_arb_cache[i].lock);
}