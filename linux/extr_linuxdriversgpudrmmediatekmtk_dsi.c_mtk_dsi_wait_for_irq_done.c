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
typedef  int u32 ;
struct mtk_dsi {int irq_data; int /*<<< orphan*/  irq_wait_queue; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*,int) ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  mtk_dsi_enable (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_reset_engine (struct mtk_dsi*) ; 
 scalar_t__ wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static s32 mtk_dsi_wait_for_irq_done(struct mtk_dsi *dsi, u32 irq_flag,
				     unsigned int timeout)
{
	s32 ret = 0;
	unsigned long jiffies = msecs_to_jiffies(timeout);

	ret = wait_event_interruptible_timeout(dsi->irq_wait_queue,
					       dsi->irq_data & irq_flag,
					       jiffies);
	if (ret == 0) {
		DRM_WARN("Wait DSI IRQ(0x%08x) Timeout\n", irq_flag);

		mtk_dsi_enable(dsi);
		mtk_dsi_reset_engine(dsi);
	}

	return ret;
}