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
typedef  scalar_t__ u32 ;
struct intel_guc_ct_channel {int enabled; int /*<<< orphan*/  owner; TYPE_1__* ctbs; int /*<<< orphan*/  vma; } ;
struct intel_guc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CTB_RECV ; 
 int CTB_SEND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  INTEL_GUC_CT_BUFFER_TYPE_RECV ; 
 int /*<<< orphan*/  INTEL_GUC_CT_BUFFER_TYPE_SEND ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  guc_action_deregister_ct_buffer (struct intel_guc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int guc_action_register_ct_buffer (struct intel_guc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guc_ct_buffer_desc_init (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_guc_ggtt_offset (struct intel_guc*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ctch_enable(struct intel_guc *guc,
		       struct intel_guc_ct_channel *ctch)
{
	u32 base;
	int err;
	int i;

	GEM_BUG_ON(!ctch->vma);

	GEM_BUG_ON(ctch->enabled);

	/* vma should be already allocated and map'ed */
	base = intel_guc_ggtt_offset(guc, ctch->vma);

	/* (re)initialize descriptors
	 * cmds buffers are in the second half of the blob page
	 */
	for (i = 0; i < ARRAY_SIZE(ctch->ctbs); i++) {
		GEM_BUG_ON((i != CTB_SEND) && (i != CTB_RECV));
		guc_ct_buffer_desc_init(ctch->ctbs[i].desc,
					base + PAGE_SIZE/4 * i + PAGE_SIZE/2,
					PAGE_SIZE/4,
					ctch->owner);
	}

	/* register buffers, starting wirh RECV buffer
	 * descriptors are in first half of the blob
	 */
	err = guc_action_register_ct_buffer(guc,
					    base + PAGE_SIZE/4 * CTB_RECV,
					    INTEL_GUC_CT_BUFFER_TYPE_RECV);
	if (unlikely(err))
		goto err_out;

	err = guc_action_register_ct_buffer(guc,
					    base + PAGE_SIZE/4 * CTB_SEND,
					    INTEL_GUC_CT_BUFFER_TYPE_SEND);
	if (unlikely(err))
		goto err_deregister;

	ctch->enabled = true;

	return 0;

err_deregister:
	guc_action_deregister_ct_buffer(guc,
					ctch->owner,
					INTEL_GUC_CT_BUFFER_TYPE_RECV);
err_out:
	DRM_ERROR("CT: can't open channel %d; err=%d\n", ctch->owner, err);
	return err;
}