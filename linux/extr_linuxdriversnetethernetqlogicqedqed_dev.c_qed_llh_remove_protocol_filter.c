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
 int BIT (int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,...) ; 
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
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qed_llh_remove_protocol_filter(struct qed_hwfn *p_hwfn,
			       struct qed_ptt *p_ptt,
			       u16 source_port_or_eth_type,
			       u16 dest_port,
			       enum qed_llh_port_filter_type_t type)
{
	u32 high = 0, low = 0;
	int i;

	if (!test_bit(QED_MF_LLH_PROTO_CLSS, &p_hwfn->cdev->mf_bits))
		return;

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
		return;
	}

	for (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) {
		if (!qed_rd(p_hwfn, p_ptt,
			    NIG_REG_LLH_FUNC_FILTER_EN + i * sizeof(u32)))
			continue;
		if (!qed_rd(p_hwfn, p_ptt,
			    NIG_REG_LLH_FUNC_FILTER_MODE + i * sizeof(u32)))
			continue;
		if (!(qed_rd(p_hwfn, p_ptt,
			     NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE +
			     i * sizeof(u32)) & BIT(type)))
			continue;
		if (qed_rd(p_hwfn, p_ptt,
			   NIG_REG_LLH_FUNC_FILTER_VALUE +
			   2 * i * sizeof(u32)) != low)
			continue;
		if (qed_rd(p_hwfn, p_ptt,
			   NIG_REG_LLH_FUNC_FILTER_VALUE +
			   (2 * i + 1) * sizeof(u32)) != high)
			continue;

		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_EN + i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_MODE + i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE +
		       i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE + 2 * i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE +
		       (2 * i + 1) * sizeof(u32), 0);
		break;
	}

	if (i >= NIG_REG_LLH_FUNC_FILTER_EN_SIZE)
		DP_NOTICE(p_hwfn, "Tried to remove a non-configured filter\n");
}