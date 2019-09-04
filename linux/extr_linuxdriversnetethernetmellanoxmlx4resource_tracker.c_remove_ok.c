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
struct res_xrcdn {int dummy; } ;
struct res_srq {int dummy; } ;
struct res_qp {int dummy; } ;
struct res_mtt {int dummy; } ;
struct res_mpt {int dummy; } ;
struct res_fs_rule {int dummy; } ;
struct res_eq {int dummy; } ;
struct res_cq {int dummy; } ;
struct res_counter {int dummy; } ;
struct res_common {int dummy; } ;
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  RES_COUNTER 137 
#define  RES_CQ 136 
#define  RES_EQ 135 
#define  RES_FS_RULE 134 
#define  RES_MAC 133 
#define  RES_MPT 132 
#define  RES_MTT 131 
#define  RES_QP 130 
#define  RES_SRQ 129 
#define  RES_XRCD 128 
 int remove_counter_ok (struct res_counter*) ; 
 int remove_cq_ok (struct res_cq*) ; 
 int remove_eq_ok (struct res_eq*) ; 
 int remove_fs_rule_ok (struct res_fs_rule*) ; 
 int remove_mpt_ok (struct res_mpt*) ; 
 int remove_mtt_ok (struct res_mtt*,int) ; 
 int remove_qp_ok (struct res_qp*) ; 
 int remove_srq_ok (struct res_srq*) ; 
 int remove_xrcdn_ok (struct res_xrcdn*) ; 

__attribute__((used)) static int remove_ok(struct res_common *res, enum mlx4_resource type, int extra)
{
	switch (type) {
	case RES_QP:
		return remove_qp_ok((struct res_qp *)res);
	case RES_CQ:
		return remove_cq_ok((struct res_cq *)res);
	case RES_SRQ:
		return remove_srq_ok((struct res_srq *)res);
	case RES_MPT:
		return remove_mpt_ok((struct res_mpt *)res);
	case RES_MTT:
		return remove_mtt_ok((struct res_mtt *)res, extra);
	case RES_MAC:
		return -EOPNOTSUPP;
	case RES_EQ:
		return remove_eq_ok((struct res_eq *)res);
	case RES_COUNTER:
		return remove_counter_ok((struct res_counter *)res);
	case RES_XRCD:
		return remove_xrcdn_ok((struct res_xrcdn *)res);
	case RES_FS_RULE:
		return remove_fs_rule_ok((struct res_fs_rule *)res);
	default:
		return -EINVAL;
	}
}