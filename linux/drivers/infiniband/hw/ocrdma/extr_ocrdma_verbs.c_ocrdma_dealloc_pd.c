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
struct ocrdma_ucontext {int dummy; } ;
struct ocrdma_pd {int id; struct ocrdma_ucontext* uctx; scalar_t__ dpp_enabled; } ;
struct TYPE_2__ {int db_page_size; scalar_t__ dpp_unmapped_addr; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  _ocrdma_dealloc_pd (struct ocrdma_dev*,struct ocrdma_pd*) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 struct ocrdma_pd* get_ocrdma_pd (struct ib_pd*) ; 
 scalar_t__ is_ucontext_pd (struct ocrdma_ucontext*,struct ocrdma_pd*) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (struct ocrdma_ucontext*,scalar_t__,int) ; 
 scalar_t__ ocrdma_get_db_addr (struct ocrdma_dev*,int) ; 
 int /*<<< orphan*/  ocrdma_release_ucontext_pd (struct ocrdma_ucontext*) ; 

void ocrdma_dealloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	struct ocrdma_dev *dev = get_ocrdma_dev(ibpd->device);
	struct ocrdma_ucontext *uctx = NULL;
	u64 usr_db;

	uctx = pd->uctx;
	if (uctx) {
		u64 dpp_db = dev->nic_info.dpp_unmapped_addr +
			(pd->id * PAGE_SIZE);
		if (pd->dpp_enabled)
			ocrdma_del_mmap(pd->uctx, dpp_db, PAGE_SIZE);
		usr_db = ocrdma_get_db_addr(dev, pd->id);
		ocrdma_del_mmap(pd->uctx, usr_db, dev->nic_info.db_page_size);

		if (is_ucontext_pd(uctx, pd)) {
			ocrdma_release_ucontext_pd(uctx);
			return;
		}
	}
	_ocrdma_dealloc_pd(dev, pd);
}