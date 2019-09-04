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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct rdma_nla_ls_gid {int dummy; } ;
struct rdma_ls_resolve_header {int dummy; } ;
typedef  int ib_sa_comp_mask ;

/* Variables and functions */
 int IB_SA_PATH_REC_DGID ; 
 int IB_SA_PATH_REC_PKEY ; 
 int IB_SA_PATH_REC_QOS_CLASS ; 
 int IB_SA_PATH_REC_SERVICE_ID ; 
 int IB_SA_PATH_REC_SGID ; 
 int IB_SA_PATH_REC_TRAFFIC_CLASS ; 
 scalar_t__ NLMSG_ALIGN (int) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ nla_total_size (int) ; 

__attribute__((used)) static int ib_nl_get_path_rec_attrs_len(ib_sa_comp_mask comp_mask)
{
	int len = 0;

	if (comp_mask & IB_SA_PATH_REC_SERVICE_ID)
		len += nla_total_size(sizeof(u64));
	if (comp_mask & IB_SA_PATH_REC_DGID)
		len += nla_total_size(sizeof(struct rdma_nla_ls_gid));
	if (comp_mask & IB_SA_PATH_REC_SGID)
		len += nla_total_size(sizeof(struct rdma_nla_ls_gid));
	if (comp_mask & IB_SA_PATH_REC_TRAFFIC_CLASS)
		len += nla_total_size(sizeof(u8));
	if (comp_mask & IB_SA_PATH_REC_PKEY)
		len += nla_total_size(sizeof(u16));
	if (comp_mask & IB_SA_PATH_REC_QOS_CLASS)
		len += nla_total_size(sizeof(u16));

	/*
	 * Make sure that at least some of the required comp_mask bits are
	 * set.
	 */
	if (WARN_ON(len == 0))
		return len;

	/* Add the family header */
	len += NLMSG_ALIGN(sizeof(struct rdma_ls_resolve_header));

	return len;
}