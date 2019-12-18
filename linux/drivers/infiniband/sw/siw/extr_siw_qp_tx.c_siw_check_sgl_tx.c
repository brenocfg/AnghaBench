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
struct TYPE_2__ {int num_sge; struct siw_sge* sge; } ;
struct siw_wqe {int /*<<< orphan*/ * mem; TYPE_1__ sqe; } ;
struct siw_sge {scalar_t__ length; } ;
struct ib_pd {int dummy; } ;
typedef  enum ib_access_flags { ____Placeholder_ib_access_flags } ib_access_flags ;

/* Variables and functions */
 int EINVAL ; 
 int E_ACCESS_OK ; 
 int SIW_MAX_SGE ; 
 int siw_check_sge (struct ib_pd*,struct siw_sge*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int siw_check_sgl_tx(struct ib_pd *pd, struct siw_wqe *wqe,
			    enum ib_access_flags perms)
{
	struct siw_sge *sge = &wqe->sqe.sge[0];
	int i, len, num_sge = wqe->sqe.num_sge;

	if (unlikely(num_sge > SIW_MAX_SGE))
		return -EINVAL;

	for (i = 0, len = 0; num_sge; num_sge--, i++, sge++) {
		/*
		 * rdma verbs: do not check stag for a zero length sge
		 */
		if (sge->length) {
			int rv = siw_check_sge(pd, sge, &wqe->mem[i], perms, 0,
					       sge->length);

			if (unlikely(rv != E_ACCESS_OK))
				return rv;
		}
		len += sge->length;
	}
	return len;
}