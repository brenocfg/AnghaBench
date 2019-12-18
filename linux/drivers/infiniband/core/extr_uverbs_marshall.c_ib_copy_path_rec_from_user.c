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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct sa_path_rec {int /*<<< orphan*/  packet_life_time_selector; int /*<<< orphan*/  preference; int /*<<< orphan*/  packet_life_time; int /*<<< orphan*/  rate; int /*<<< orphan*/  rate_selector; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mtu_selector; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  numb_path; int /*<<< orphan*/  reversible; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; TYPE_2__ sgid; TYPE_1__ dgid; int /*<<< orphan*/  rec_type; } ;
struct ib_user_path_rec {int /*<<< orphan*/  packet_life_time_selector; int /*<<< orphan*/  preference; int /*<<< orphan*/  packet_life_time; int /*<<< orphan*/  rate; int /*<<< orphan*/  rate_selector; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mtu_selector; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  numb_path; int /*<<< orphan*/  reversible; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  raw_traffic; scalar_t__ sgid; scalar_t__ dgid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  slid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_PATH_REC_TYPE_IB ; 
 int /*<<< orphan*/  SA_PATH_REC_TYPE_OPA ; 
 scalar_t__ ib_is_opa_gid (union ib_gid*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct sa_path_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_get_lid_from_gid (union ib_gid*) ; 
 int /*<<< orphan*/  sa_path_set_dlid (struct sa_path_rec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_path_set_dmac_zero (struct sa_path_rec*) ; 
 int /*<<< orphan*/  sa_path_set_raw_traffic (struct sa_path_rec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_path_set_slid (struct sa_path_rec*,int /*<<< orphan*/ ) ; 

void ib_copy_path_rec_from_user(struct sa_path_rec *dst,
				struct ib_user_path_rec *src)
{
	u32 slid, dlid;

	memset(dst, 0, sizeof(*dst));
	if ((ib_is_opa_gid((union ib_gid *)src->sgid)) ||
	    (ib_is_opa_gid((union ib_gid *)src->dgid))) {
		dst->rec_type = SA_PATH_REC_TYPE_OPA;
		slid = opa_get_lid_from_gid((union ib_gid *)src->sgid);
		dlid = opa_get_lid_from_gid((union ib_gid *)src->dgid);
	} else {
		dst->rec_type = SA_PATH_REC_TYPE_IB;
		slid = ntohs(src->slid);
		dlid = ntohs(src->dlid);
	}
	memcpy(dst->dgid.raw, src->dgid, sizeof dst->dgid);
	memcpy(dst->sgid.raw, src->sgid, sizeof dst->sgid);

	sa_path_set_dlid(dst, dlid);
	sa_path_set_slid(dst, slid);
	sa_path_set_raw_traffic(dst, src->raw_traffic);
	dst->flow_label		= src->flow_label;
	dst->hop_limit		= src->hop_limit;
	dst->traffic_class	= src->traffic_class;
	dst->reversible		= src->reversible;
	dst->numb_path		= src->numb_path;
	dst->pkey		= src->pkey;
	dst->sl			= src->sl;
	dst->mtu_selector	= src->mtu_selector;
	dst->mtu		= src->mtu;
	dst->rate_selector	= src->rate_selector;
	dst->rate		= src->rate;
	dst->packet_life_time	= src->packet_life_time;
	dst->preference		= src->preference;
	dst->packet_life_time_selector = src->packet_life_time_selector;

	/* TODO: No need to set this */
	sa_path_set_dmac_zero(dst);
}