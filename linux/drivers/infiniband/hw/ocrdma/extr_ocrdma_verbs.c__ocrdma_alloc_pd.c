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
struct ocrdma_ucontext {int dummy; } ;
struct ocrdma_pd {int dpp_enabled; int num_dpp_qp; } ;
struct TYPE_6__ {int wqe_size; scalar_t__ max_dpp_pds; } ;
struct TYPE_4__ {int db_page_size; } ;
struct ocrdma_dev {TYPE_2__* pd_mgr; TYPE_3__ attr; TYPE_1__ nic_info; } ;
struct ib_udata {int dummy; } ;
struct TYPE_5__ {scalar_t__ pd_prealloc_valid; } ;

/* Variables and functions */
 scalar_t__ OCRDMA_ASIC_GEN_SKH_R ; 
 scalar_t__ ocrdma_get_asic_type (struct ocrdma_dev*) ; 
 int ocrdma_get_pd_num (struct ocrdma_dev*,struct ocrdma_pd*) ; 
 int ocrdma_mbx_alloc_pd (struct ocrdma_dev*,struct ocrdma_pd*) ; 

__attribute__((used)) static int _ocrdma_alloc_pd(struct ocrdma_dev *dev, struct ocrdma_pd *pd,
			    struct ocrdma_ucontext *uctx,
			    struct ib_udata *udata)
{
	int status;

	if (udata && uctx && dev->attr.max_dpp_pds) {
		pd->dpp_enabled =
			ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R;
		pd->num_dpp_qp =
			pd->dpp_enabled ? (dev->nic_info.db_page_size /
					   dev->attr.wqe_size) : 0;
	}

	if (dev->pd_mgr->pd_prealloc_valid)
		return ocrdma_get_pd_num(dev, pd);

retry:
	status = ocrdma_mbx_alloc_pd(dev, pd);
	if (status) {
		if (pd->dpp_enabled) {
			pd->dpp_enabled = false;
			pd->num_dpp_qp = 0;
			goto retry;
		}
		return status;
	}

	return 0;
}