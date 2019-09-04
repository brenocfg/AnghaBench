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
typedef  int /*<<< orphan*/  uint32_t ;
struct smu10_hwmgr {int /*<<< orphan*/  gfx_max_freq_limit; int /*<<< orphan*/  gfx_min_freq_limit; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static uint32_t smu10_dpm_get_sclk(struct pp_hwmgr *hwmgr, bool low)
{
	struct smu10_hwmgr *data;

	if (hwmgr == NULL)
		return -EINVAL;

	data = (struct smu10_hwmgr *)(hwmgr->backend);

	if (low)
		return data->gfx_min_freq_limit;
	else
		return data->gfx_max_freq_limit;
}