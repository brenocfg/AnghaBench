#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct siw_sqe {int rkey; int /*<<< orphan*/  access; scalar_t__ base_mr; } ;
struct siw_mem {int stag_valid; int stag; int /*<<< orphan*/  va; int /*<<< orphan*/  perms; struct ib_pd* pd; } ;
struct siw_device {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_mr {int rkey; int /*<<< orphan*/  iova; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  siw_dbg_mem (struct siw_mem*,char*,int) ; 
 int /*<<< orphan*/  siw_dbg_pd (struct ib_pd*,char*,int) ; 
 struct siw_mem* siw_mem_id2obj (struct siw_device*,int) ; 
 int /*<<< orphan*/  siw_mem_put (struct siw_mem*) ; 
 struct siw_device* to_siw_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int siw_fastreg_mr(struct ib_pd *pd, struct siw_sqe *sqe)
{
	struct ib_mr *base_mr = (struct ib_mr *)(uintptr_t)sqe->base_mr;
	struct siw_device *sdev = to_siw_dev(pd->device);
	struct siw_mem *mem = siw_mem_id2obj(sdev, sqe->rkey  >> 8);
	int rv = 0;

	siw_dbg_pd(pd, "STag 0x%08x\n", sqe->rkey);

	if (unlikely(!mem || !base_mr)) {
		pr_warn("siw: fastreg: STag 0x%08x unknown\n", sqe->rkey);
		return -EINVAL;
	}
	if (unlikely(base_mr->rkey >> 8 != sqe->rkey  >> 8)) {
		pr_warn("siw: fastreg: STag 0x%08x: bad MR\n", sqe->rkey);
		rv = -EINVAL;
		goto out;
	}
	if (unlikely(mem->pd != pd)) {
		pr_warn("siw: fastreg: PD mismatch\n");
		rv = -EINVAL;
		goto out;
	}
	if (unlikely(mem->stag_valid)) {
		pr_warn("siw: fastreg: STag 0x%08x already valid\n", sqe->rkey);
		rv = -EINVAL;
		goto out;
	}
	/* Refresh STag since user may have changed key part */
	mem->stag = sqe->rkey;
	mem->perms = sqe->access;

	siw_dbg_mem(mem, "STag 0x%08x now valid\n", sqe->rkey);
	mem->va = base_mr->iova;
	mem->stag_valid = 1;
out:
	siw_mem_put(mem);
	return rv;
}