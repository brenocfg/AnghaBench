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
struct dpaa_bp {size_t bpid; int /*<<< orphan*/  pool; scalar_t__ free_buf_cb; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bman_free_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** dpaa_bp_array ; 
 int /*<<< orphan*/  dpaa_bp_drain (struct dpaa_bp*) ; 
 struct dpaa_bp* dpaa_bpid2pool (size_t) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpaa_bp_free(struct dpaa_bp *dpaa_bp)
{
	struct dpaa_bp *bp = dpaa_bpid2pool(dpaa_bp->bpid);

	/* the mapping between bpid and dpaa_bp is done very late in the
	 * allocation procedure; if something failed before the mapping, the bp
	 * was not configured, therefore we don't need the below instructions
	 */
	if (!bp)
		return;

	if (!refcount_dec_and_test(&bp->refs))
		return;

	if (bp->free_buf_cb)
		dpaa_bp_drain(bp);

	dpaa_bp_array[bp->bpid] = NULL;
	bman_free_pool(bp->pool);
}