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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_4__ {int num_pbes; int num_pbls; int pbl_size; } ;
struct ocrdma_mr {TYPE_2__ hwmr; } ;
struct TYPE_3__ {int max_num_mr_pbl; } ;
struct ocrdma_dev {TYPE_1__ attr; } ;

/* Variables and functions */
 int EFAULT ; 
 int MAX_OCRDMA_PBL_SIZE ; 
 int OCRDMA_MIN_HPAGE_SIZE ; 
 int roundup (int,int) ; 

__attribute__((used)) static int ocrdma_get_pbl_info(struct ocrdma_dev *dev, struct ocrdma_mr *mr,
			      u32 num_pbes)
{
	u32 num_pbls = 0;
	u32 idx = 0;
	int status = 0;
	u32 pbl_size;

	do {
		pbl_size = OCRDMA_MIN_HPAGE_SIZE * (1 << idx);
		if (pbl_size > MAX_OCRDMA_PBL_SIZE) {
			status = -EFAULT;
			break;
		}
		num_pbls = roundup(num_pbes, (pbl_size / sizeof(u64)));
		num_pbls = num_pbls / (pbl_size / sizeof(u64));
		idx++;
	} while (num_pbls >= dev->attr.max_num_mr_pbl);

	mr->hwmr.num_pbes = num_pbes;
	mr->hwmr.num_pbls = num_pbls;
	mr->hwmr.pbl_size = pbl_size;
	return status;
}