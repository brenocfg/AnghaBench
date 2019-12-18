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
struct qedr_pbl {int /*<<< orphan*/  pa; int /*<<< orphan*/  list_entry; } ;
struct qedr_dev {int dummy; } ;
struct mr_info {int /*<<< orphan*/  free_pbl_list; int /*<<< orphan*/  pbl_info; struct qedr_pbl* pbl_table; int /*<<< orphan*/  inuse_pbl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct qedr_pbl*) ; 
 int PTR_ERR (struct qedr_pbl*) ; 
 int /*<<< orphan*/  QEDR_MSG_MR ; 
 int /*<<< orphan*/  free_mr_info (struct qedr_dev*,struct mr_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* qedr_alloc_pbl_tbl (struct qedr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qedr_prepare_pbl_tbl (struct qedr_dev*,int /*<<< orphan*/ *,size_t,int) ; 

__attribute__((used)) static int init_mr_info(struct qedr_dev *dev, struct mr_info *info,
			size_t page_list_len, bool two_layered)
{
	struct qedr_pbl *tmp;
	int rc;

	INIT_LIST_HEAD(&info->free_pbl_list);
	INIT_LIST_HEAD(&info->inuse_pbl_list);

	rc = qedr_prepare_pbl_tbl(dev, &info->pbl_info,
				  page_list_len, two_layered);
	if (rc)
		goto done;

	info->pbl_table = qedr_alloc_pbl_tbl(dev, &info->pbl_info, GFP_KERNEL);
	if (IS_ERR(info->pbl_table)) {
		rc = PTR_ERR(info->pbl_table);
		goto done;
	}

	DP_DEBUG(dev, QEDR_MSG_MR, "pbl_table_pa = %pa\n",
		 &info->pbl_table->pa);

	/* in usual case we use 2 PBLs, so we add one to free
	 * list and allocating another one
	 */
	tmp = qedr_alloc_pbl_tbl(dev, &info->pbl_info, GFP_KERNEL);
	if (IS_ERR(tmp)) {
		DP_DEBUG(dev, QEDR_MSG_MR, "Extra PBL is not allocated\n");
		goto done;
	}

	list_add_tail(&tmp->list_entry, &info->free_pbl_list);

	DP_DEBUG(dev, QEDR_MSG_MR, "extra pbl_table_pa = %pa\n", &tmp->pa);

done:
	if (rc)
		free_mr_info(dev, info);

	return rc;
}