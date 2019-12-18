#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_14__ {int /*<<< orphan*/ * rcfw; int /*<<< orphan*/  dpi_tbl; } ;
struct bnxt_re_dev {int num_msix; TYPE_5__ qplib_res; int /*<<< orphan*/  dpi_privileged; TYPE_6__* nq; int /*<<< orphan*/  chip_ctx; TYPE_4__* msix_entries; TYPE_1__* en_dev; int /*<<< orphan*/  dev_attr; int /*<<< orphan*/  netdev; int /*<<< orphan*/  is_virtfn; int /*<<< orphan*/  rcfw; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {size_t level; TYPE_2__* pbl; scalar_t__ max_elements; } ;
struct TYPE_15__ {int /*<<< orphan*/  ring_id; TYPE_3__ hwq; TYPE_5__* res; } ;
struct TYPE_13__ {int /*<<< orphan*/  ring_idx; } ;
struct TYPE_11__ {int pg_count; int /*<<< orphan*/ * pg_map_arr; } ;
struct TYPE_10__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ BNXT_QPLIB_NQE_MAX_CNT ; 
 scalar_t__ BNXT_RE_MAX_CQ_COUNT ; 
 scalar_t__ BNXT_RE_MAX_SRQC_COUNT ; 
 size_t PBL_LVL_0 ; 
 int bnxt_qplib_alloc_dpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bnxt_re_dev*) ; 
 int bnxt_qplib_alloc_nq (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int bnxt_qplib_alloc_res (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_dealloc_dpi (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_free_nq (TYPE_6__*) ; 
 int /*<<< orphan*/  bnxt_qplib_free_res (TYPE_5__*) ; 
 int bnxt_qplib_get_dev_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_get_ring_type (int /*<<< orphan*/ *) ; 
 int bnxt_re_net_ring_alloc (struct bnxt_re_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_net_ring_free (struct bnxt_re_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 

__attribute__((used)) static int bnxt_re_alloc_res(struct bnxt_re_dev *rdev)
{
	int num_vec_created = 0;
	dma_addr_t *pg_map;
	int rc = 0, i;
	int pages;
	u8 type;

	/* Configure and allocate resources for qplib */
	rdev->qplib_res.rcfw = &rdev->rcfw;
	rc = bnxt_qplib_get_dev_attr(&rdev->rcfw, &rdev->dev_attr,
				     rdev->is_virtfn);
	if (rc)
		goto fail;

	rc = bnxt_qplib_alloc_res(&rdev->qplib_res, rdev->en_dev->pdev,
				  rdev->netdev, &rdev->dev_attr);
	if (rc)
		goto fail;

	rc = bnxt_qplib_alloc_dpi(&rdev->qplib_res.dpi_tbl,
				  &rdev->dpi_privileged,
				  rdev);
	if (rc)
		goto dealloc_res;

	for (i = 0; i < rdev->num_msix - 1; i++) {
		rdev->nq[i].res = &rdev->qplib_res;
		rdev->nq[i].hwq.max_elements = BNXT_RE_MAX_CQ_COUNT +
			BNXT_RE_MAX_SRQC_COUNT + 2;
		rc = bnxt_qplib_alloc_nq(rdev->en_dev->pdev, &rdev->nq[i]);
		if (rc) {
			dev_err(rdev_to_dev(rdev), "Alloc Failed NQ%d rc:%#x",
				i, rc);
			goto free_nq;
		}
		type = bnxt_qplib_get_ring_type(&rdev->chip_ctx);
		pg_map = rdev->nq[i].hwq.pbl[PBL_LVL_0].pg_map_arr;
		pages = rdev->nq[i].hwq.pbl[rdev->nq[i].hwq.level].pg_count;
		rc = bnxt_re_net_ring_alloc(rdev, pg_map, pages, type,
					    BNXT_QPLIB_NQE_MAX_CNT - 1,
					    rdev->msix_entries[i + 1].ring_idx,
					    &rdev->nq[i].ring_id);
		if (rc) {
			dev_err(rdev_to_dev(rdev),
				"Failed to allocate NQ fw id with rc = 0x%x",
				rc);
			bnxt_qplib_free_nq(&rdev->nq[i]);
			goto free_nq;
		}
		num_vec_created++;
	}
	return 0;
free_nq:
	for (i = num_vec_created; i >= 0; i--) {
		type = bnxt_qplib_get_ring_type(&rdev->chip_ctx);
		bnxt_re_net_ring_free(rdev, rdev->nq[i].ring_id, type);
		bnxt_qplib_free_nq(&rdev->nq[i]);
	}
	bnxt_qplib_dealloc_dpi(&rdev->qplib_res,
			       &rdev->qplib_res.dpi_tbl,
			       &rdev->dpi_privileged);
dealloc_res:
	bnxt_qplib_free_res(&rdev->qplib_res);

fail:
	rdev->qplib_res.rcfw = NULL;
	return rc;
}