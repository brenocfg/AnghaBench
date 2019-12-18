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
struct bfa_tskim_s {int dummy; } ;
struct bfa_ioim_sp_s {int dummy; } ;
struct bfa_ioim_s {int dummy; } ;
struct TYPE_2__ {int num_ioim_reqs; int num_tskim_reqs; } ;
struct bfa_iocfc_cfg_s {TYPE_1__ fwcfg; } ;

/* Variables and functions */
 int BFA_TSKIM_MIN ; 
 int /*<<< orphan*/  bfa_itnim_meminfo (struct bfa_iocfc_cfg_s*,int*) ; 

__attribute__((used)) static void
bfa_fcpim_meminfo(struct bfa_iocfc_cfg_s *cfg, u32 *km_len)
{
	bfa_itnim_meminfo(cfg, km_len);

	/*
	 * IO memory
	 */
	*km_len += cfg->fwcfg.num_ioim_reqs *
	  (sizeof(struct bfa_ioim_s) + sizeof(struct bfa_ioim_sp_s));

	/*
	 * task management command memory
	 */
	if (cfg->fwcfg.num_tskim_reqs < BFA_TSKIM_MIN)
		cfg->fwcfg.num_tskim_reqs = BFA_TSKIM_MIN;
	*km_len += cfg->fwcfg.num_tskim_reqs * sizeof(struct bfa_tskim_s);
}