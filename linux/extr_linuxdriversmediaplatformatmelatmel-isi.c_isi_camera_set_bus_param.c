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
struct TYPE_2__ {scalar_t__ full_mode; scalar_t__ has_emb_sync; scalar_t__ pclk_act_falling; scalar_t__ vsync_act_low; scalar_t__ hsync_act_low; } ;
struct atmel_isi {int /*<<< orphan*/  dev; TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISI_CFG1 ; 
 int /*<<< orphan*/  ISI_CFG1_EMB_SYNC ; 
 int /*<<< orphan*/  ISI_CFG1_FULL_MODE ; 
 int /*<<< orphan*/  ISI_CFG1_HSYNC_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  ISI_CFG1_PIXCLK_POL_ACTIVE_FALLING ; 
 int /*<<< orphan*/  ISI_CFG1_THMASK_BEATS_16 ; 
 int /*<<< orphan*/  ISI_CFG1_VSYNC_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  ISI_CTRL ; 
 int /*<<< orphan*/  ISI_CTRL_DIS ; 
 int /*<<< orphan*/  isi_writel (struct atmel_isi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isi_camera_set_bus_param(struct atmel_isi *isi)
{
	u32 cfg1 = 0;

	/* set bus param for ISI */
	if (isi->pdata.hsync_act_low)
		cfg1 |= ISI_CFG1_HSYNC_POL_ACTIVE_LOW;
	if (isi->pdata.vsync_act_low)
		cfg1 |= ISI_CFG1_VSYNC_POL_ACTIVE_LOW;
	if (isi->pdata.pclk_act_falling)
		cfg1 |= ISI_CFG1_PIXCLK_POL_ACTIVE_FALLING;
	if (isi->pdata.has_emb_sync)
		cfg1 |= ISI_CFG1_EMB_SYNC;
	if (isi->pdata.full_mode)
		cfg1 |= ISI_CFG1_FULL_MODE;

	cfg1 |= ISI_CFG1_THMASK_BEATS_16;

	/* Enable PM and peripheral clock before operate isi registers */
	pm_runtime_get_sync(isi->dev);

	isi_writel(isi, ISI_CTRL, ISI_CTRL_DIS);
	isi_writel(isi, ISI_CFG1, cfg1);

	pm_runtime_put(isi->dev);
}