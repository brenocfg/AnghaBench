#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cxl_afu {TYPE_3__* adapter; scalar_t__ num_procs; scalar_t__ current_mode; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* afu_reset ) (struct cxl_afu*) ;} ;
struct TYPE_7__ {TYPE_2__* native; } ;
struct TYPE_6__ {TYPE_1__* sl_ops; } ;
struct TYPE_5__ {scalar_t__ needs_reset_before_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_afu_disable (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_chardev_afu_remove (struct cxl_afu*) ; 
 TYPE_4__* cxl_ops ; 
 int /*<<< orphan*/  cxl_psl_purge (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_sysfs_afu_m_remove (struct cxl_afu*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct cxl_afu*) ; 

__attribute__((used)) static int deactivate_afu_directed(struct cxl_afu *afu)
{
	dev_info(&afu->dev, "Deactivating AFU directed mode\n");

	afu->current_mode = 0;
	afu->num_procs = 0;

	cxl_sysfs_afu_m_remove(afu);
	cxl_chardev_afu_remove(afu);

	/*
	 * The CAIA section 2.2.1 indicates that the procedure for starting and
	 * stopping an AFU in AFU directed mode is AFU specific, which is not
	 * ideal since this code is generic and with one exception has no
	 * knowledge of the AFU. This is in contrast to the procedure for
	 * disabling a dedicated process AFU, which is documented to just
	 * require a reset. The architecture does indicate that both an AFU
	 * reset and an AFU disable should result in the AFU being disabled and
	 * we do both followed by a PSL purge for safety.
	 *
	 * Notably we used to have some issues with the disable sequence on PSL
	 * cards, which is why we ended up using this heavy weight procedure in
	 * the first place, however a bug was discovered that had rendered the
	 * disable operation ineffective, so it is conceivable that was the
	 * sole explanation for those difficulties. Careful regression testing
	 * is recommended if anyone attempts to remove or reorder these
	 * operations.
	 *
	 * The XSL on the Mellanox CX4 behaves a little differently from the
	 * PSL based cards and will time out an AFU reset if the AFU is still
	 * enabled. That card is special in that we do have a means to identify
	 * it from this code, so in that case we skip the reset and just use a
	 * disable/purge to avoid the timeout and corresponding noise in the
	 * kernel log.
	 */
	if (afu->adapter->native->sl_ops->needs_reset_before_disable)
		cxl_ops->afu_reset(afu);
	cxl_afu_disable(afu);
	cxl_psl_purge(afu);

	return 0;
}