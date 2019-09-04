#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  v4_addr; int /*<<< orphan*/  v6_addr; } ;
struct iscsi_path {TYPE_1__ src; int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  handle; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct cnic_sock {int /*<<< orphan*/  flags; int /*<<< orphan*/ * ha; int /*<<< orphan*/ * src_ip; int /*<<< orphan*/  vlan_id; } ;
struct cnic_local {struct cnic_sock* csk_tbl; int /*<<< orphan*/ * ulp_ops; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 size_t CNIC_ULP_L4 ; 
 int EINVAL ; 
 int ENODEV ; 
 int ETH_ALEN ; 
#define  ISCSI_UEVENT_PATH_UPDATE 128 
 int /*<<< orphan*/  L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE ; 
 int MAX_CM_SK_TBL_SZ ; 
 int /*<<< orphan*/  SK_F_CONNECT_START ; 
 int /*<<< orphan*/  SK_F_IPV6 ; 
 int /*<<< orphan*/  SK_F_OFFLD_COMPLETE ; 
 int /*<<< orphan*/  SK_F_OFFLD_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_cm_set_pg (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_cm_upcall (struct cnic_local*,struct cnic_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_in_use (struct cnic_sock*) ; 
 int /*<<< orphan*/  csk_hold (struct cnic_sock*) ; 
 int /*<<< orphan*/  csk_put (struct cnic_sock*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_iscsi_nl_msg_recv(struct cnic_dev *dev, u32 msg_type,
				  char *buf, u16 len)
{
	int rc = -EINVAL;

	switch (msg_type) {
	case ISCSI_UEVENT_PATH_UPDATE: {
		struct cnic_local *cp;
		u32 l5_cid;
		struct cnic_sock *csk;
		struct iscsi_path *path_resp;

		if (len < sizeof(*path_resp))
			break;

		path_resp = (struct iscsi_path *) buf;
		cp = dev->cnic_priv;
		l5_cid = (u32) path_resp->handle;
		if (l5_cid >= MAX_CM_SK_TBL_SZ)
			break;

		if (!rcu_access_pointer(cp->ulp_ops[CNIC_ULP_L4])) {
			rc = -ENODEV;
			break;
		}
		csk = &cp->csk_tbl[l5_cid];
		csk_hold(csk);
		if (cnic_in_use(csk) &&
		    test_bit(SK_F_CONNECT_START, &csk->flags)) {

			csk->vlan_id = path_resp->vlan_id;

			memcpy(csk->ha, path_resp->mac_addr, ETH_ALEN);
			if (test_bit(SK_F_IPV6, &csk->flags))
				memcpy(&csk->src_ip[0], &path_resp->src.v6_addr,
				       sizeof(struct in6_addr));
			else
				memcpy(&csk->src_ip[0], &path_resp->src.v4_addr,
				       sizeof(struct in_addr));

			if (is_valid_ether_addr(csk->ha)) {
				cnic_cm_set_pg(csk);
			} else if (!test_bit(SK_F_OFFLD_SCHED, &csk->flags) &&
				!test_bit(SK_F_OFFLD_COMPLETE, &csk->flags)) {

				cnic_cm_upcall(cp, csk,
					L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE);
				clear_bit(SK_F_CONNECT_START, &csk->flags);
			}
		}
		csk_put(csk);
		rc = 0;
	}
	}

	return rc;
}