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
typedef  int u16 ;
struct qed_dev {int dummy; } ;
typedef  enum qed_llh_prot_filter_type_t { ____Placeholder_qed_llh_prot_filter_type_t } qed_llh_prot_filter_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int) ; 
 int EINVAL ; 
#define  QED_LLH_FILTER_ETHERTYPE 134 
#define  QED_LLH_FILTER_TCP_DEST_PORT 133 
#define  QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT 132 
#define  QED_LLH_FILTER_TCP_SRC_PORT 131 
#define  QED_LLH_FILTER_UDP_DEST_PORT 130 
#define  QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT 129 
#define  QED_LLH_FILTER_UDP_SRC_PORT 128 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,size_t,char*,int,...) ; 

__attribute__((used)) static int
qed_llh_protocol_filter_stringify(struct qed_dev *cdev,
				  enum qed_llh_prot_filter_type_t type,
				  u16 source_port_or_eth_type,
				  u16 dest_port, u8 *str, size_t str_len)
{
	switch (type) {
	case QED_LLH_FILTER_ETHERTYPE:
		snprintf(str, str_len, "Ethertype 0x%04x",
			 source_port_or_eth_type);
		break;
	case QED_LLH_FILTER_TCP_SRC_PORT:
		snprintf(str, str_len, "TCP src port 0x%04x",
			 source_port_or_eth_type);
		break;
	case QED_LLH_FILTER_UDP_SRC_PORT:
		snprintf(str, str_len, "UDP src port 0x%04x",
			 source_port_or_eth_type);
		break;
	case QED_LLH_FILTER_TCP_DEST_PORT:
		snprintf(str, str_len, "TCP dst port 0x%04x", dest_port);
		break;
	case QED_LLH_FILTER_UDP_DEST_PORT:
		snprintf(str, str_len, "UDP dst port 0x%04x", dest_port);
		break;
	case QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT:
		snprintf(str, str_len, "TCP src/dst ports 0x%04x/0x%04x",
			 source_port_or_eth_type, dest_port);
		break;
	case QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT:
		snprintf(str, str_len, "UDP src/dst ports 0x%04x/0x%04x",
			 source_port_or_eth_type, dest_port);
		break;
	default:
		DP_NOTICE(cdev,
			  "Non valid LLH protocol filter type %d\n", type);
		return -EINVAL;
	}

	return 0;
}