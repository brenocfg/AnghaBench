#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num_reqq_elems; scalar_t__ num_rspq_elems; scalar_t__ num_sgpgs; } ;
struct TYPE_3__ {scalar_t__ num_rports; scalar_t__ num_ioim_reqs; scalar_t__ num_tskim_reqs; scalar_t__ num_fcxp_reqs; scalar_t__ num_uf_bufs; } ;
struct bfa_iocfc_cfg_s {TYPE_2__ drvcfg; TYPE_1__ fwcfg; } ;

/* Variables and functions */
 scalar_t__ BFA_FCXP_MAX ; 
 scalar_t__ BFA_SGPG_MAX ; 
 scalar_t__ BFA_UF_MAX ; 
 scalar_t__ num_fcxps ; 
 scalar_t__ num_ios ; 
 scalar_t__ num_rports ; 
 scalar_t__ num_sgpgs ; 
 scalar_t__ num_tms ; 
 scalar_t__ num_ufbufs ; 
 scalar_t__ reqq_size ; 
 scalar_t__ rspq_size ; 

void
bfad_update_hal_cfg(struct bfa_iocfc_cfg_s *bfa_cfg)
{
	if (num_rports > 0)
		bfa_cfg->fwcfg.num_rports = num_rports;
	if (num_ios > 0)
		bfa_cfg->fwcfg.num_ioim_reqs = num_ios;
	if (num_tms > 0)
		bfa_cfg->fwcfg.num_tskim_reqs = num_tms;
	if (num_fcxps > 0 && num_fcxps <= BFA_FCXP_MAX)
		bfa_cfg->fwcfg.num_fcxp_reqs = num_fcxps;
	if (num_ufbufs > 0 && num_ufbufs <= BFA_UF_MAX)
		bfa_cfg->fwcfg.num_uf_bufs = num_ufbufs;
	if (reqq_size > 0)
		bfa_cfg->drvcfg.num_reqq_elems = reqq_size;
	if (rspq_size > 0)
		bfa_cfg->drvcfg.num_rspq_elems = rspq_size;
	if (num_sgpgs > 0 && num_sgpgs <= BFA_SGPG_MAX)
		bfa_cfg->drvcfg.num_sgpgs = num_sgpgs;

	/*
	 * populate the hal values back to the driver for sysfs use.
	 * otherwise, the default values will be shown as 0 in sysfs
	 */
	num_rports = bfa_cfg->fwcfg.num_rports;
	num_ios = bfa_cfg->fwcfg.num_ioim_reqs;
	num_tms = bfa_cfg->fwcfg.num_tskim_reqs;
	num_fcxps = bfa_cfg->fwcfg.num_fcxp_reqs;
	num_ufbufs = bfa_cfg->fwcfg.num_uf_bufs;
	reqq_size = bfa_cfg->drvcfg.num_reqq_elems;
	rspq_size = bfa_cfg->drvcfg.num_rspq_elems;
	num_sgpgs = bfa_cfg->drvcfg.num_sgpgs;
}