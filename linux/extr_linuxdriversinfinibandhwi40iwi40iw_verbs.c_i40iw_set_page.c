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
typedef  int /*<<< orphan*/  u64 ;
struct ib_mr {int dummy; } ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct i40iw_pble_alloc {TYPE_1__ level1; } ;
struct i40iw_pbl {struct i40iw_pble_alloc pble_alloc; } ;
struct i40iw_mr {scalar_t__ npages; scalar_t__ page_cnt; struct i40iw_pbl iwpbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct i40iw_mr* to_iwmr (struct ib_mr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int i40iw_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct i40iw_mr *iwmr = to_iwmr(ibmr);
	struct i40iw_pbl *iwpbl = &iwmr->iwpbl;
	struct i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	u64 *pbl;

	if (unlikely(iwmr->npages == iwmr->page_cnt))
		return -ENOMEM;

	pbl = (u64 *)palloc->level1.addr;
	pbl[iwmr->npages++] = cpu_to_le64(addr);
	return 0;
}