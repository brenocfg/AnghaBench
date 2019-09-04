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
struct npu_context {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* release_cb ) (struct npu_context*,int /*<<< orphan*/ ) ;} ;
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmio_invalidate (struct npu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct npu_context* mn_to_npu_context (struct mmu_notifier*) ; 
 int /*<<< orphan*/  stub1 (struct npu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnv_npu2_mn_release(struct mmu_notifier *mn,
				struct mm_struct *mm)
{
	struct npu_context *npu_context = mn_to_npu_context(mn);

	/* Call into device driver to stop requests to the NMMU */
	if (npu_context->release_cb)
		npu_context->release_cb(npu_context, npu_context->priv);

	/*
	 * There should be no more translation requests for this PID, but we
	 * need to ensure any entries for it are removed from the TLB.
	 */
	mmio_invalidate(npu_context, 0, 0, true);
}