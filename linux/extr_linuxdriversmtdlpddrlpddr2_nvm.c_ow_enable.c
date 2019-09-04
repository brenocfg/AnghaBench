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
struct pcm_int_data {scalar_t__ ctl_regs; int /*<<< orphan*/  bus_width; } ;
struct map_info {struct pcm_int_data* fldrv_priv; } ;

/* Variables and functions */
 scalar_t__ LPDDR2_MODE_REG_CFG ; 
 scalar_t__ LPDDR2_MODE_REG_DATA ; 
 int build_mr_cfgmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void ow_enable(struct map_info *map)
{
	struct pcm_int_data *pcm_data = map->fldrv_priv;

	writel_relaxed(build_mr_cfgmask(pcm_data->bus_width) | 0x18,
		pcm_data->ctl_regs + LPDDR2_MODE_REG_CFG);
	writel_relaxed(0x01, pcm_data->ctl_regs + LPDDR2_MODE_REG_DATA);
}