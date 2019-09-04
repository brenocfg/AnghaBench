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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mtk_dsi {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  mtk_dsi_irq_data_clear (struct mtk_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dsi_set_cmd_mode (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_wait_for_irq_done (struct mtk_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 mtk_dsi_switch_to_cmd_mode(struct mtk_dsi *dsi, u8 irq_flag, u32 t)
{
	mtk_dsi_irq_data_clear(dsi, irq_flag);
	mtk_dsi_set_cmd_mode(dsi);

	if (!mtk_dsi_wait_for_irq_done(dsi, irq_flag, t)) {
		DRM_ERROR("failed to switch cmd mode\n");
		return -ETIME;
	} else {
		return 0;
	}
}