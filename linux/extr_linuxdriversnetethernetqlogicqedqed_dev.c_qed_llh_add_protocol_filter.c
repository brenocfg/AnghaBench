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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
typedef  enum qed_llh_port_filter_type_t { ____Placeholder_qed_llh_port_filter_type_t } qed_llh_port_filter_type_t ;
struct TYPE_2__ {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_EN ; 
 int NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_MODE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_VALUE ; 
#define  QED_LLH_FILTER_ETHERTYPE 134 
#define  QED_LLH_FILTER_TCP_DEST_PORT 133 
#define  QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT 132 
#define  QED_LLH_FILTER_TCP_SRC_PORT 131 
#define  QED_LLH_FILTER_UDP_DEST_PORT 130 
#define  QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT 129 
#define  QED_LLH_FILTER_UDP_SRC_PORT 128 
 int /*<<< orphan*/  QED_MF_LLH_PROTO_CLSS ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qed_llh_add_protocol_filter(struct qed_hwfn *p_hwfn,
			    struct qed_ptt *p_ptt,
			    u16 source_port_or_eth_type,
			    u16 dest_port, enum qed_llh_port_filter_type_t type)
{
	u32 high = 0, low = 0, en;
	int i;

	if (!test_bit(QED_MF_LLH_PROTO_CLSS, &p_hwfn->cdev->mf_bits))
		return 0;

	switch (type) {
	case QED_LLH_FILTER_ETHERTYPE:
		high = source_port_or_eth_type;
		break;
	case QED_LLH_FILTER_TCP_SRC_PORT:
	case QED_LLH_FILTER_UDP_SRC_PORT:
		low = source_port_or_eth_type << 16;
		break;
	case QED_LLH_FILTER_TCP_DEST_PORT:
	case QED_LLH_FILTER_UDP_DEST_PORT:
		low = dest_port;
		break;
	case QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT:
	case QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT:
		low = (source_port_or_eth_type << 16) | dest_port;
		break;
	default:
		DP_NOTICE(p_hwfn,
			  "Non valid LLH protocol filter type %d\n", type);
		return -EINVAL;
	}
	/* Find a free entry and utilize it */
	for (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) {
		en = qed_rd(p_hwfn, p_ptt,
			    NIG_REG_LLH_FUNC_FILTER_EN + i * sizeof(u32));
		if (en)
			continue;
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE +
		       2 * i * sizeof(u32), low);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE +
		       (2 * i + 1) * sizeof(u32), high);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_MODE + i * sizeof(u32), 1);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE +
		       i * sizeof(u32), 1 << type);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_EN + i * sizeof(u32), 1);
		break;
	}
	if (i >= NIG_REG_LLH_FUNC_FILTER_EN_SIZE) {
		DP_NOTICE(p_hwfn,
			  "Failed to find an empty LLH filter to utilize\n");
		return -EINVAL;
	}
	switch (type) {
	case QED_LLH_FILTER_ETHERTYPE:
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "ETH type %x is added at %d\n",
			   source_port_or_eth_type, i);
		break;
	case QED_LLH_FILTER_TCP_SRC_PORT:
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "TCP src port %x is added at %d\n",
			   source_port_or_eth_type, i);
		break;
	case QED_LLH_FILTER_UDP_SRC_PORT:
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "UDP src port %x is added at %d\n",
			   source_port_or_eth_type, i);
		break;
	case QED_LLH_FILTER_TCP_DEST_PORT:
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "TCP dst port %x is added at %d\n", dest_port, i);
		break;
	case QED_LLH_FILTER_UDP_DEST_PORT:
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "UDP dst port %x is added at %d\n", dest_port, i);
		break;
	case QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT:
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "TCP src/dst ports %x/%x are added at %d\n",
			   source_port_or_eth_type, dest_port, i);
		break;
	case QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT:
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "UDP src/dst ports %x/%x are added at %d\n",
			   source_port_or_eth_type, dest_port, i);
		break;
	}
	return 0;
}