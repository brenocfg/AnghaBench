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
struct vfpf_init_tlv {int flags; scalar_t__ sb_addr; int /*<<< orphan*/  stats_stride; int /*<<< orphan*/  stats_addr; } ;
struct bnx2x_virtf {int cfg_flags; int /*<<< orphan*/  index; int /*<<< orphan*/  stats_stride; int /*<<< orphan*/  fw_stat_map; } ;
struct bnx2x_vf_mbx {TYPE_2__* msg; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct vfpf_init_tlv init; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int VFPF_INIT_FLG_STATS_COALESCE ; 
 int VF_CFG_EXT_BULLETIN ; 
 int VF_CFG_STATS_COALESCE ; 
 int /*<<< orphan*/  bnx2x_iov_link_update_vf (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int bnx2x_vf_init (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp (struct bnx2x*,struct bnx2x_virtf*,int) ; 

__attribute__((used)) static void bnx2x_vf_mbx_init_vf(struct bnx2x *bp, struct bnx2x_virtf *vf,
			      struct bnx2x_vf_mbx *mbx)
{
	struct vfpf_init_tlv *init = &mbx->msg->req.init;
	int rc;

	/* record ghost addresses from vf message */
	vf->fw_stat_map = init->stats_addr;
	vf->stats_stride = init->stats_stride;
	rc = bnx2x_vf_init(bp, vf, (dma_addr_t *)init->sb_addr);

	/* set VF multiqueue statistics collection mode */
	if (init->flags & VFPF_INIT_FLG_STATS_COALESCE)
		vf->cfg_flags |= VF_CFG_STATS_COALESCE;

	/* Update VF's view of link state */
	if (vf->cfg_flags & VF_CFG_EXT_BULLETIN)
		bnx2x_iov_link_update_vf(bp, vf->index);

	/* response */
	bnx2x_vf_mbx_resp(bp, vf, rc);
}