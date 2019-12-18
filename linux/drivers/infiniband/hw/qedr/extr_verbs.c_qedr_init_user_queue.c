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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct qedr_userq {size_t buf_len; int /*<<< orphan*/ * umem; int /*<<< orphan*/ * pbl_tbl; int /*<<< orphan*/  pbl_info; int /*<<< orphan*/  buf_addr; } ;
struct qedr_dev {int dummy; } ;
struct ib_udata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int) ; 
 int ENOMEM ; 
 int FW_PAGE_SHIFT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ib_umem_get (struct ib_udata*,int /*<<< orphan*/ ,size_t,int,int) ; 
 int ib_umem_page_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qedr_alloc_pbl_tbl (struct qedr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_populate_pbls (struct qedr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int qedr_prepare_pbl_tbl (struct qedr_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qedr_init_user_queue(struct ib_udata *udata,
				       struct qedr_dev *dev,
				       struct qedr_userq *q, u64 buf_addr,
				       size_t buf_len, int access, int dmasync,
				       int alloc_and_init)
{
	u32 fw_pages;
	int rc;

	q->buf_addr = buf_addr;
	q->buf_len = buf_len;
	q->umem = ib_umem_get(udata, q->buf_addr, q->buf_len, access, dmasync);
	if (IS_ERR(q->umem)) {
		DP_ERR(dev, "create user queue: failed ib_umem_get, got %ld\n",
		       PTR_ERR(q->umem));
		return PTR_ERR(q->umem);
	}

	fw_pages = ib_umem_page_count(q->umem) <<
	    (PAGE_SHIFT - FW_PAGE_SHIFT);

	rc = qedr_prepare_pbl_tbl(dev, &q->pbl_info, fw_pages, 0);
	if (rc)
		goto err0;

	if (alloc_and_init) {
		q->pbl_tbl = qedr_alloc_pbl_tbl(dev, &q->pbl_info, GFP_KERNEL);
		if (IS_ERR(q->pbl_tbl)) {
			rc = PTR_ERR(q->pbl_tbl);
			goto err0;
		}
		qedr_populate_pbls(dev, q->umem, q->pbl_tbl, &q->pbl_info,
				   FW_PAGE_SHIFT);
	} else {
		q->pbl_tbl = kzalloc(sizeof(*q->pbl_tbl), GFP_KERNEL);
		if (!q->pbl_tbl) {
			rc = -ENOMEM;
			goto err0;
		}
	}

	return 0;

err0:
	ib_umem_release(q->umem);
	q->umem = NULL;

	return rc;
}