#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct smu_table_context {TYPE_11__* driver_pptable; } ;
struct smu_dpm_context {struct smu_11_0_dpm_context* dpm_context; } ;
struct smu_context {struct smu_table_context smu_table; struct smu_dpm_context smu_dpm; } ;
struct TYPE_22__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_21__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_20__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_19__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_18__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_17__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_16__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_15__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_14__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_12__ {TYPE_9__ phy_table; TYPE_8__ display_table; TYPE_7__ pixel_table; TYPE_6__ dcef_table; TYPE_5__ dclk_table; TYPE_4__ vclk_table; TYPE_3__ uclk_table; TYPE_2__ gfx_table; TYPE_1__ soc_table; } ;
struct smu_11_0_dpm_context {TYPE_10__ dpm_tables; } ;
struct TYPE_13__ {int /*<<< orphan*/ * FreqTablePhyclk; int /*<<< orphan*/ * FreqTableDispclk; int /*<<< orphan*/ * FreqTablePixclk; int /*<<< orphan*/ * FreqTableDcefclk; int /*<<< orphan*/ * FreqTableDclk; int /*<<< orphan*/ * FreqTableVclk; int /*<<< orphan*/ * FreqTableUclk; int /*<<< orphan*/ * FreqTableGfx; int /*<<< orphan*/ * FreqTableSocclk; } ;
typedef  TYPE_11__ PPTable_t ;

/* Variables and functions */
 int NUM_DCEFCLK_DPM_LEVELS ; 
 int NUM_DCLK_DPM_LEVELS ; 
 int NUM_DISPCLK_DPM_LEVELS ; 
 int NUM_GFXCLK_DPM_LEVELS ; 
 int NUM_PHYCLK_DPM_LEVELS ; 
 int NUM_PIXCLK_DPM_LEVELS ; 
 int NUM_SOCCLK_DPM_LEVELS ; 
 int NUM_UCLK_DPM_LEVELS ; 
 int NUM_VCLK_DPM_LEVELS ; 

__attribute__((used)) static int navi10_set_default_dpm_table(struct smu_context *smu)
{
	struct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	struct smu_table_context *table_context = &smu->smu_table;
	struct smu_11_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	PPTable_t *driver_ppt = NULL;

	driver_ppt = table_context->driver_pptable;

	dpm_context->dpm_tables.soc_table.min = driver_ppt->FreqTableSocclk[0];
	dpm_context->dpm_tables.soc_table.max = driver_ppt->FreqTableSocclk[NUM_SOCCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.gfx_table.min = driver_ppt->FreqTableGfx[0];
	dpm_context->dpm_tables.gfx_table.max = driver_ppt->FreqTableGfx[NUM_GFXCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.uclk_table.min = driver_ppt->FreqTableUclk[0];
	dpm_context->dpm_tables.uclk_table.max = driver_ppt->FreqTableUclk[NUM_UCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.vclk_table.min = driver_ppt->FreqTableVclk[0];
	dpm_context->dpm_tables.vclk_table.max = driver_ppt->FreqTableVclk[NUM_VCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.dclk_table.min = driver_ppt->FreqTableDclk[0];
	dpm_context->dpm_tables.dclk_table.max = driver_ppt->FreqTableDclk[NUM_DCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.dcef_table.min = driver_ppt->FreqTableDcefclk[0];
	dpm_context->dpm_tables.dcef_table.max = driver_ppt->FreqTableDcefclk[NUM_DCEFCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.pixel_table.min = driver_ppt->FreqTablePixclk[0];
	dpm_context->dpm_tables.pixel_table.max = driver_ppt->FreqTablePixclk[NUM_PIXCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.display_table.min = driver_ppt->FreqTableDispclk[0];
	dpm_context->dpm_tables.display_table.max = driver_ppt->FreqTableDispclk[NUM_DISPCLK_DPM_LEVELS - 1];

	dpm_context->dpm_tables.phy_table.min = driver_ppt->FreqTablePhyclk[0];
	dpm_context->dpm_tables.phy_table.max = driver_ppt->FreqTablePhyclk[NUM_PHYCLK_DPM_LEVELS - 1];

	return 0;
}