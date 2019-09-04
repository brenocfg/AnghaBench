#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfp_cpp {int dummy; } ;
struct nfp_abm_link {int /*<<< orphan*/  id; TYPE_2__* abm; } ;
struct TYPE_6__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  target; } ;
struct TYPE_5__ {TYPE_3__* q_lvls; TYPE_1__* app; } ;
struct TYPE_4__ {struct nfp_cpp* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_CPP_ATOMIC_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_q_lvl_thrs (struct nfp_abm_link*,unsigned int) ; 
 int nfp_cpp_writel (struct nfp_cpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int /*<<< orphan*/ ,unsigned int) ; 

int nfp_abm_ctrl_set_q_lvl(struct nfp_abm_link *alink, unsigned int i, u32 val)
{
	struct nfp_cpp *cpp = alink->abm->app->cpp;
	u32 muw;
	int err;

	muw = NFP_CPP_ATOMIC_WR(alink->abm->q_lvls->target,
				alink->abm->q_lvls->domain);

	err = nfp_cpp_writel(cpp, muw, nfp_abm_q_lvl_thrs(alink, i), val);
	if (err) {
		nfp_err(cpp, "RED offload setting level failed on vNIC %d queue %d\n",
			alink->id, i);
		return err;
	}

	return 0;
}