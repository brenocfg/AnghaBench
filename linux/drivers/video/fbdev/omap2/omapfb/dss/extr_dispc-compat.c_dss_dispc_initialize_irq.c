#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  last_reset; } ;
struct TYPE_5__ {int /*<<< orphan*/  error_work; int /*<<< orphan*/  irq_error_mask; int /*<<< orphan*/  registered_isr; int /*<<< orphan*/  irq_lock; TYPE_1__ irq_stats; int /*<<< orphan*/  irq_stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQ_MASK_ERROR ; 
 int /*<<< orphan*/  DISPC_IRQ_SYNC_LOST2 ; 
 int /*<<< orphan*/  DISPC_IRQ_SYNC_LOST3 ; 
 int /*<<< orphan*/  DISPC_IRQ_VID3_FIFO_UNDERFLOW ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  FEAT_MGR_LCD2 ; 
 int /*<<< orphan*/  FEAT_MGR_LCD3 ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _omap_dispc_set_irqs () ; 
 int /*<<< orphan*/  dispc_clear_irqstatus (int /*<<< orphan*/ ) ; 
 TYPE_2__ dispc_compat ; 
 int /*<<< orphan*/  dispc_dump_irqs ; 
 int /*<<< orphan*/  dispc_error_worker ; 
 int /*<<< orphan*/  dispc_read_irqstatus () ; 
 int dispc_request_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (char*,int /*<<< orphan*/ ) ; 
 int dss_feat_get_num_ovls () ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_dispc_irq_handler ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int dss_dispc_initialize_irq(void)
{
	int r;

#ifdef CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
	spin_lock_init(&dispc_compat.irq_stats_lock);
	dispc_compat.irq_stats.last_reset = jiffies;
	dss_debugfs_create_file("dispc_irq", dispc_dump_irqs);
#endif

	spin_lock_init(&dispc_compat.irq_lock);

	memset(dispc_compat.registered_isr, 0,
			sizeof(dispc_compat.registered_isr));

	dispc_compat.irq_error_mask = DISPC_IRQ_MASK_ERROR;
	if (dss_has_feature(FEAT_MGR_LCD2))
		dispc_compat.irq_error_mask |= DISPC_IRQ_SYNC_LOST2;
	if (dss_has_feature(FEAT_MGR_LCD3))
		dispc_compat.irq_error_mask |= DISPC_IRQ_SYNC_LOST3;
	if (dss_feat_get_num_ovls() > 3)
		dispc_compat.irq_error_mask |= DISPC_IRQ_VID3_FIFO_UNDERFLOW;

	/*
	 * there's SYNC_LOST_DIGIT waiting after enabling the DSS,
	 * so clear it
	 */
	dispc_clear_irqstatus(dispc_read_irqstatus());

	INIT_WORK(&dispc_compat.error_work, dispc_error_worker);

	_omap_dispc_set_irqs();

	r = dispc_request_irq(omap_dispc_irq_handler, &dispc_compat);
	if (r) {
		DSSERR("dispc_request_irq failed\n");
		return r;
	}

	return 0;
}