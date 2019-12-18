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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dispc_mgr_get_framedone_irq (int) ; 
 int /*<<< orphan*/  dispc_mgr_get_vsync_irq (int) ; 
 int /*<<< orphan*/  dss_apply_irq_handler ; 
 TYPE_1__ dss_data ; 
 int dss_feat_get_num_mgrs () ; 
 int omap_dispc_unregister_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dss_unregister_vsync_isr(void)
{
	const int num_mgrs = dss_feat_get_num_mgrs();
	u32 mask;
	int r, i;

	mask = 0;
	for (i = 0; i < num_mgrs; ++i)
		mask |= dispc_mgr_get_vsync_irq(i);

	for (i = 0; i < num_mgrs; ++i)
		mask |= dispc_mgr_get_framedone_irq(i);

	r = omap_dispc_unregister_isr(dss_apply_irq_handler, NULL, mask);
	WARN_ON(r);

	dss_data.irq_enabled = false;
}