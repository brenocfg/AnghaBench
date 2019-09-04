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
struct vfpf_rss_tlv {scalar_t__ ind_table_size; scalar_t__ rss_key_size; int rss_flags; int /*<<< orphan*/  rss_result_mask; int /*<<< orphan*/  rss_key; int /*<<< orphan*/  ind_table; } ;
struct bnx2x_virtf {int /*<<< orphan*/  rss_conf_obj; int /*<<< orphan*/  index; } ;
struct bnx2x_vf_mbx {TYPE_2__* msg; } ;
struct bnx2x_config_rss_params {scalar_t__ rss_flags; scalar_t__ ramrod_flags; int /*<<< orphan*/  rss_result_mask; int /*<<< orphan*/ * rss_obj; int /*<<< orphan*/  rss_key; int /*<<< orphan*/  ind_table; } ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {struct vfpf_rss_tlv update_rss; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4 ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_TCP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_UDP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6 ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_TCP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_UDP ; 
 int /*<<< orphan*/  BNX2X_RSS_MODE_DISABLED ; 
 int /*<<< orphan*/  BNX2X_RSS_MODE_REGULAR ; 
 int /*<<< orphan*/  BNX2X_RSS_SET_SRCH ; 
 int EINVAL ; 
 scalar_t__ T_ETH_INDIRECTION_TABLE_SIZE ; 
 scalar_t__ T_ETH_RSS_KEY ; 
 int VFPF_RSS_IPV4 ; 
 int VFPF_RSS_IPV4_TCP ; 
 int VFPF_RSS_IPV4_UDP ; 
 int VFPF_RSS_IPV6 ; 
 int VFPF_RSS_IPV6_TCP ; 
 int VFPF_RSS_IPV6_UDP ; 
 int VFPF_RSS_MODE_DISABLED ; 
 int VFPF_RSS_MODE_REGULAR ; 
 int VFPF_RSS_SET_SRCH ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int bnx2x_vf_rss_update (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_config_rss_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct bnx2x_config_rss_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_vf_mbx_update_rss(struct bnx2x *bp, struct bnx2x_virtf *vf,
				    struct bnx2x_vf_mbx *mbx)
{
	struct bnx2x_config_rss_params rss;
	struct vfpf_rss_tlv *rss_tlv = &mbx->msg->req.update_rss;
	int rc = 0;

	if (rss_tlv->ind_table_size != T_ETH_INDIRECTION_TABLE_SIZE ||
	    rss_tlv->rss_key_size != T_ETH_RSS_KEY) {
		BNX2X_ERR("failing rss configuration of vf %d due to size mismatch\n",
			  vf->index);
		rc = -EINVAL;
		goto mbx_resp;
	}

	memset(&rss, 0, sizeof(struct bnx2x_config_rss_params));

	/* set vfop params according to rss tlv */
	memcpy(rss.ind_table, rss_tlv->ind_table,
	       T_ETH_INDIRECTION_TABLE_SIZE);
	memcpy(rss.rss_key, rss_tlv->rss_key, sizeof(rss_tlv->rss_key));
	rss.rss_obj = &vf->rss_conf_obj;
	rss.rss_result_mask = rss_tlv->rss_result_mask;

	/* flags handled individually for backward/forward compatibility */
	rss.rss_flags = 0;
	rss.ramrod_flags = 0;

	if (rss_tlv->rss_flags & VFPF_RSS_MODE_DISABLED)
		__set_bit(BNX2X_RSS_MODE_DISABLED, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_MODE_REGULAR)
		__set_bit(BNX2X_RSS_MODE_REGULAR, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_SET_SRCH)
		__set_bit(BNX2X_RSS_SET_SRCH, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_IPV4)
		__set_bit(BNX2X_RSS_IPV4, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_IPV4_TCP)
		__set_bit(BNX2X_RSS_IPV4_TCP, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_IPV4_UDP)
		__set_bit(BNX2X_RSS_IPV4_UDP, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_IPV6)
		__set_bit(BNX2X_RSS_IPV6, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_IPV6_TCP)
		__set_bit(BNX2X_RSS_IPV6_TCP, &rss.rss_flags);
	if (rss_tlv->rss_flags & VFPF_RSS_IPV6_UDP)
		__set_bit(BNX2X_RSS_IPV6_UDP, &rss.rss_flags);

	if ((!(rss_tlv->rss_flags & VFPF_RSS_IPV4_TCP) &&
	     rss_tlv->rss_flags & VFPF_RSS_IPV4_UDP) ||
	    (!(rss_tlv->rss_flags & VFPF_RSS_IPV6_TCP) &&
	     rss_tlv->rss_flags & VFPF_RSS_IPV6_UDP)) {
		BNX2X_ERR("about to hit a FW assert. aborting...\n");
		rc = -EINVAL;
		goto mbx_resp;
	}

	rc = bnx2x_vf_rss_update(bp, vf, &rss);
mbx_resp:
	bnx2x_vf_mbx_resp(bp, vf, rc);
}