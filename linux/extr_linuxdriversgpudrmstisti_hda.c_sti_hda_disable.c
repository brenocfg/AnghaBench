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
typedef  int /*<<< orphan*/  u32 ;
struct sti_hda {int enabled; int /*<<< orphan*/  clk_pix; int /*<<< orphan*/  clk_hddac; } ;
struct drm_bridge {struct sti_hda* driver_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_AWG_ASYNC_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  HDA_ANA_ANC_CTRL ; 
 int /*<<< orphan*/  HDA_ANA_CFG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_enable_hd_dacs (struct sti_hda*,int) ; 
 int /*<<< orphan*/  hda_read (struct sti_hda*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_write (struct sti_hda*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_hda_disable(struct drm_bridge *bridge)
{
	struct sti_hda *hda = bridge->driver_private;
	u32 val;

	if (!hda->enabled)
		return;

	DRM_DEBUG_DRIVER("\n");

	/* Disable HD DAC and AWG */
	val = hda_read(hda, HDA_ANA_CFG);
	val &= ~CFG_AWG_ASYNC_EN;
	hda_write(hda, val, HDA_ANA_CFG);
	hda_write(hda, 0, HDA_ANA_ANC_CTRL);

	hda_enable_hd_dacs(hda, false);

	/* Disable/unprepare hda clock */
	clk_disable_unprepare(hda->clk_hddac);
	clk_disable_unprepare(hda->clk_pix);

	hda->enabled = false;
}