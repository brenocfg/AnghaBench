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
typedef  int /*<<< orphan*/  u16 ;
struct ib_sa_mcmember_data {scalar_t__ qkey; scalar_t__ mlid; scalar_t__ tclass; scalar_t__ pkey; int scope_join_state; int /*<<< orphan*/  sl_flowlabel_hoplimit; int /*<<< orphan*/  lifetmsel_lifetm; int /*<<< orphan*/  ratesel_rate; int /*<<< orphan*/  mtusel_mtu; } ;
typedef  int ib_sa_comp_mask ;

/* Variables and functions */
 int IB_SA_MCMEMBER_REC_FLOW_LABEL ; 
 int IB_SA_MCMEMBER_REC_HOP_LIMIT ; 
 int IB_SA_MCMEMBER_REC_MLID ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_MTU ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_MTU_SELECTOR ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_PKEY ; 
 int IB_SA_MCMEMBER_REC_QKEY ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_RATE ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_RATE_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_SCOPE ; 
 int IB_SA_MCMEMBER_REC_SL ; 
 int IB_SA_MCMEMBER_REC_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  MAD_STATUS_REQ_INVALID ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ check_selector (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 cmp_rec(struct ib_sa_mcmember_data *src,
		   struct ib_sa_mcmember_data *dst, ib_sa_comp_mask comp_mask)
{
	/* src is group record, dst is request record */
	/* MGID must already match */
	/* Port_GID we always replace to our Port_GID, so it is a match */

#define MAD_STATUS_REQ_INVALID 0x0200
	if (comp_mask & IB_SA_MCMEMBER_REC_QKEY && src->qkey != dst->qkey)
		return MAD_STATUS_REQ_INVALID;
	if (comp_mask & IB_SA_MCMEMBER_REC_MLID && src->mlid != dst->mlid)
		return MAD_STATUS_REQ_INVALID;
	if (check_selector(comp_mask, IB_SA_MCMEMBER_REC_MTU_SELECTOR,
				 IB_SA_MCMEMBER_REC_MTU,
				 src->mtusel_mtu, dst->mtusel_mtu))
		return MAD_STATUS_REQ_INVALID;
	if (comp_mask & IB_SA_MCMEMBER_REC_TRAFFIC_CLASS &&
	    src->tclass != dst->tclass)
		return MAD_STATUS_REQ_INVALID;
	if (comp_mask & IB_SA_MCMEMBER_REC_PKEY && src->pkey != dst->pkey)
		return MAD_STATUS_REQ_INVALID;
	if (check_selector(comp_mask, IB_SA_MCMEMBER_REC_RATE_SELECTOR,
				 IB_SA_MCMEMBER_REC_RATE,
				 src->ratesel_rate, dst->ratesel_rate))
		return MAD_STATUS_REQ_INVALID;
	if (check_selector(comp_mask,
				 IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR,
				 IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME,
				 src->lifetmsel_lifetm, dst->lifetmsel_lifetm))
		return MAD_STATUS_REQ_INVALID;
	if (comp_mask & IB_SA_MCMEMBER_REC_SL &&
			(be32_to_cpu(src->sl_flowlabel_hoplimit) & 0xf0000000) !=
			(be32_to_cpu(dst->sl_flowlabel_hoplimit) & 0xf0000000))
		return MAD_STATUS_REQ_INVALID;
	if (comp_mask & IB_SA_MCMEMBER_REC_FLOW_LABEL &&
			(be32_to_cpu(src->sl_flowlabel_hoplimit) & 0x0fffff00) !=
			(be32_to_cpu(dst->sl_flowlabel_hoplimit) & 0x0fffff00))
		return MAD_STATUS_REQ_INVALID;
	if (comp_mask & IB_SA_MCMEMBER_REC_HOP_LIMIT &&
			(be32_to_cpu(src->sl_flowlabel_hoplimit) & 0x000000ff) !=
			(be32_to_cpu(dst->sl_flowlabel_hoplimit) & 0x000000ff))
		return MAD_STATUS_REQ_INVALID;
	if (comp_mask & IB_SA_MCMEMBER_REC_SCOPE &&
			(src->scope_join_state & 0xf0) !=
			(dst->scope_join_state & 0xf0))
		return MAD_STATUS_REQ_INVALID;

	/* join_state checked separately, proxy_join ignored */

	return 0;
}