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
typedef  int u32 ;
struct bfa_itnim_s {int dummy; } ;
struct TYPE_2__ {int num_rports; } ;
struct bfa_iocfc_cfg_s {TYPE_1__ fwcfg; } ;

/* Variables and functions */

void
bfa_itnim_meminfo(struct bfa_iocfc_cfg_s *cfg, u32 *km_len)
{
	/*
	 * ITN memory
	 */
	*km_len += cfg->fwcfg.num_rports * sizeof(struct bfa_itnim_s);
}