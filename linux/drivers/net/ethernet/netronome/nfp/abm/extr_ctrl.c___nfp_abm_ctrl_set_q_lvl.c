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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_cpp {int dummy; } ;
struct nfp_abm {int /*<<< orphan*/ * thresholds; int /*<<< orphan*/  q_lvls; int /*<<< orphan*/  threshold_undef; TYPE_1__* app; } ;
struct TYPE_2__ {struct nfp_cpp* cpp; } ;

/* Variables and functions */
 unsigned int NFP_QLVL_STRIDE ; 
 scalar_t__ NFP_QLVL_THRS ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int __nfp_rtsym_writel (struct nfp_cpp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,unsigned int) ; 

int __nfp_abm_ctrl_set_q_lvl(struct nfp_abm *abm, unsigned int id, u32 val)
{
	struct nfp_cpp *cpp = abm->app->cpp;
	u64 sym_offset;
	int err;

	__clear_bit(id, abm->threshold_undef);
	if (abm->thresholds[id] == val)
		return 0;

	sym_offset = id * NFP_QLVL_STRIDE + NFP_QLVL_THRS;
	err = __nfp_rtsym_writel(cpp, abm->q_lvls, 4, 0, sym_offset, val);
	if (err) {
		nfp_err(cpp,
			"RED offload setting level failed on subqueue %d\n",
			id);
		return err;
	}

	abm->thresholds[id] = val;
	return 0;
}