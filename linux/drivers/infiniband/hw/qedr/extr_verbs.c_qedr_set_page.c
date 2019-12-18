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
typedef  int u32 ;
struct regpair {void* hi; void* lo; } ;
struct qedr_pbl {scalar_t__ va; } ;
struct TYPE_3__ {int num_pbes; int pbl_size; } ;
struct TYPE_4__ {struct qedr_pbl* pbl_table; TYPE_1__ pbl_info; } ;
struct qedr_mr {int npages; TYPE_2__ info; int /*<<< orphan*/  dev; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  DP_ERR (int /*<<< orphan*/ ,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QEDR_MSG_MR ; 
 void* cpu_to_le32 (int) ; 
 struct qedr_mr* get_qedr_mr (struct ib_mr*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int qedr_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct qedr_mr *mr = get_qedr_mr(ibmr);
	struct qedr_pbl *pbl_table;
	struct regpair *pbe;
	u32 pbes_in_page;

	if (unlikely(mr->npages == mr->info.pbl_info.num_pbes)) {
		DP_ERR(mr->dev, "qedr_set_page fails when %d\n", mr->npages);
		return -ENOMEM;
	}

	DP_DEBUG(mr->dev, QEDR_MSG_MR, "qedr_set_page pages[%d] = 0x%llx\n",
		 mr->npages, addr);

	pbes_in_page = mr->info.pbl_info.pbl_size / sizeof(u64);
	pbl_table = mr->info.pbl_table + (mr->npages / pbes_in_page);
	pbe = (struct regpair *)pbl_table->va;
	pbe +=  mr->npages % pbes_in_page;
	pbe->lo = cpu_to_le32((u32)addr);
	pbe->hi = cpu_to_le32((u32)upper_32_bits(addr));

	mr->npages++;

	return 0;
}