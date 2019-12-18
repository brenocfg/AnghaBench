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
struct smu_table_context {struct smu_11_0_max_sustainable_clocks* max_sustainable_clocks; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct smu_11_0_max_sustainable_clocks {scalar_t__ soc_clock; scalar_t__ uclock; scalar_t__ pixel_clock; scalar_t__ phy_clock; scalar_t__ display_clock; scalar_t__ dcef_clock; } ;
struct pp_smu_nv_clock_table {unsigned int dcfClockInKhz; unsigned int displayClockInKhz; unsigned int phyClockInKhz; unsigned int pixelClockInKhz; unsigned int uClockInKhz; unsigned int socClockInKhz; scalar_t__ fabricClockInKhz; scalar_t__ dppClockInKhz; scalar_t__ dscClockInKhz; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int smu_v11_0_get_max_sustainable_clocks_by_dc(struct smu_context *smu,
		struct pp_smu_nv_clock_table *max_clocks)
{
	struct smu_table_context *table_context = &smu->smu_table;
	struct smu_11_0_max_sustainable_clocks *sustainable_clocks = NULL;

	if (!max_clocks || !table_context->max_sustainable_clocks)
		return -EINVAL;

	sustainable_clocks = table_context->max_sustainable_clocks;

	max_clocks->dcfClockInKhz =
			(unsigned int) sustainable_clocks->dcef_clock * 1000;
	max_clocks->displayClockInKhz =
			(unsigned int) sustainable_clocks->display_clock * 1000;
	max_clocks->phyClockInKhz =
			(unsigned int) sustainable_clocks->phy_clock * 1000;
	max_clocks->pixelClockInKhz =
			(unsigned int) sustainable_clocks->pixel_clock * 1000;
	max_clocks->uClockInKhz =
			(unsigned int) sustainable_clocks->uclock * 1000;
	max_clocks->socClockInKhz =
			(unsigned int) sustainable_clocks->soc_clock * 1000;
	max_clocks->dscClockInKhz = 0;
	max_clocks->dppClockInKhz = 0;
	max_clocks->fabricClockInKhz = 0;

	return 0;
}