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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct nfp_rtsym {scalar_t__ addr; int /*<<< orphan*/  domain; int /*<<< orphan*/  target; } ;
struct nfp_cpp {int dummy; } ;
struct nfp_abm_link {unsigned int queue_base; int /*<<< orphan*/  id; TYPE_2__* abm; } ;
struct TYPE_4__ {TYPE_1__* app; } ;
struct TYPE_3__ {struct nfp_cpp* cpp; } ;

/* Variables and functions */
 scalar_t__ NFP_CPP_ATOMIC_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_cpp_readl (struct nfp_cpp*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int nfp_cpp_readq (struct nfp_cpp*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
nfp_abm_ctrl_stat(struct nfp_abm_link *alink, const struct nfp_rtsym *sym,
		  unsigned int stride, unsigned int offset, unsigned int i,
		  bool is_u64, u64 *res)
{
	struct nfp_cpp *cpp = alink->abm->app->cpp;
	u32 val32, mur;
	u64 val, addr;
	int err;

	mur = NFP_CPP_ATOMIC_RD(sym->target, sym->domain);

	addr = sym->addr + (alink->queue_base + i) * stride + offset;
	if (is_u64)
		err = nfp_cpp_readq(cpp, mur, addr, &val);
	else
		err = nfp_cpp_readl(cpp, mur, addr, &val32);
	if (err) {
		nfp_err(cpp,
			"RED offload reading stat failed on vNIC %d queue %d\n",
			alink->id, i);
		return err;
	}

	*res = is_u64 ? val : val32;
	return 0;
}