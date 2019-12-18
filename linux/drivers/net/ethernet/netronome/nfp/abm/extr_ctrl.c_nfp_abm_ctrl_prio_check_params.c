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
struct TYPE_6__ {unsigned int mbox_len; } ;
struct nfp_net {TYPE_3__ tlv_caps; } ;
struct nfp_abm_link {struct nfp_abm* abm; struct nfp_net* vnic; } ;
struct nfp_abm {unsigned int prio_map_len; TYPE_2__* app; } ;
struct TYPE_5__ {TYPE_1__* pf; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NFP_NET_ABM_MBOX_DATA ; 
 int /*<<< orphan*/  nfp_abm_has_prio (struct nfp_abm*) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int nfp_abm_ctrl_prio_check_params(struct nfp_abm_link *alink)
{
	struct nfp_abm *abm = alink->abm;
	struct nfp_net *nn = alink->vnic;
	unsigned int min_mbox_sz;

	if (!nfp_abm_has_prio(alink->abm))
		return 0;

	min_mbox_sz = NFP_NET_ABM_MBOX_DATA + alink->abm->prio_map_len;
	if (nn->tlv_caps.mbox_len < min_mbox_sz) {
		nfp_err(abm->app->pf->cpp, "vNIC mailbox too small for prio offload: %u, need: %u\n",
			nn->tlv_caps.mbox_len,  min_mbox_sz);
		return -EINVAL;
	}

	return 0;
}