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
struct efa_mr {int /*<<< orphan*/  umem; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  inline_pbl_array; } ;
struct efa_com_reg_mr_params {int inline_pbl; int /*<<< orphan*/  page_num; int /*<<< orphan*/  page_shift; TYPE_1__ pbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int umem_to_page_list (struct efa_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efa_create_inline_pbl(struct efa_dev *dev, struct efa_mr *mr,
				 struct efa_com_reg_mr_params *params)
{
	int err;

	params->inline_pbl = 1;
	err = umem_to_page_list(dev, mr->umem, params->pbl.inline_pbl_array,
				params->page_num, params->page_shift);
	if (err)
		return err;

	ibdev_dbg(&dev->ibdev,
		  "inline_pbl_array - pages[%u]\n", params->page_num);

	return 0;
}