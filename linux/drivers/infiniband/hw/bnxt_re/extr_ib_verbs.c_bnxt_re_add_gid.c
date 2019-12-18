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
typedef  size_t u32 ;
typedef  int u16 ;
struct ib_gid_attr {int /*<<< orphan*/  gid; int /*<<< orphan*/  device; } ;
struct bnxt_re_gid_ctx {int refcnt; size_t idx; } ;
struct bnxt_qplib_sgid_tbl {struct bnxt_re_gid_ctx** ctx; } ;
struct TYPE_4__ {TYPE_1__* netdev; struct bnxt_qplib_sgid_tbl sgid_tbl; } ;
struct bnxt_re_dev {TYPE_2__ qplib_res; } ;
struct bnxt_qplib_gid {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EALREADY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bnxt_qplib_add_sgid (struct bnxt_qplib_sgid_tbl*,struct bnxt_qplib_gid*,int /*<<< orphan*/ ,int,int,size_t*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ibdev ; 
 struct bnxt_re_gid_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,int*,int /*<<< orphan*/ *) ; 
 struct bnxt_re_dev* to_bnxt_re_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bnxt_re_add_gid(const struct ib_gid_attr *attr, void **context)
{
	int rc;
	u32 tbl_idx = 0;
	u16 vlan_id = 0xFFFF;
	struct bnxt_re_gid_ctx *ctx, **ctx_tbl;
	struct bnxt_re_dev *rdev = to_bnxt_re_dev(attr->device, ibdev);
	struct bnxt_qplib_sgid_tbl *sgid_tbl = &rdev->qplib_res.sgid_tbl;

	rc = rdma_read_gid_l2_fields(attr, &vlan_id, NULL);
	if (rc)
		return rc;

	rc = bnxt_qplib_add_sgid(sgid_tbl, (struct bnxt_qplib_gid *)&attr->gid,
				 rdev->qplib_res.netdev->dev_addr,
				 vlan_id, true, &tbl_idx);
	if (rc == -EALREADY) {
		ctx_tbl = sgid_tbl->ctx;
		ctx_tbl[tbl_idx]->refcnt++;
		*context = ctx_tbl[tbl_idx];
		return 0;
	}

	if (rc < 0) {
		dev_err(rdev_to_dev(rdev), "Failed to add GID: %#x", rc);
		return rc;
	}

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	ctx_tbl = sgid_tbl->ctx;
	ctx->idx = tbl_idx;
	ctx->refcnt = 1;
	ctx_tbl[tbl_idx] = ctx;
	*context = ctx;

	return rc;
}