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
typedef  int u8 ;
struct qede_dev {int rss_caps; scalar_t__ state; int /*<<< orphan*/  cdev; TYPE_1__* ops; int /*<<< orphan*/  rss_params_inited; } ;
struct qed_update_vport_params {int /*<<< orphan*/  update_rss_flg; int /*<<< orphan*/  rss_params; } ;
struct ethtool_rxnfc {int flow_type; int data; } ;
struct TYPE_2__ {int (* vport_update ) (int /*<<< orphan*/ ,struct qed_update_vport_params*) ;} ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 143 
#define  AH_ESP_V6_FLOW 142 
#define  AH_V4_FLOW 141 
#define  AH_V6_FLOW 140 
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  ESP_V4_FLOW 139 
#define  ESP_V6_FLOW 138 
#define  ETHER_FLOW 137 
#define  IPV4_FLOW 136 
#define  IPV6_FLOW 135 
#define  IP_USER_FLOW 134 
 int /*<<< orphan*/  QEDE_RSS_CAPS_INITED ; 
 scalar_t__ QEDE_STATE_OPEN ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int QED_RSS_IPV4_UDP ; 
 int QED_RSS_IPV6_UDP ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_fill_rss_params (struct qede_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_update_vport_params*) ; 
 int /*<<< orphan*/  vfree (struct qed_update_vport_params*) ; 
 struct qed_update_vport_params* vzalloc (int) ; 

__attribute__((used)) static int qede_set_rss_flags(struct qede_dev *edev, struct ethtool_rxnfc *info)
{
	struct qed_update_vport_params *vport_update_params;
	u8 set_caps = 0, clr_caps = 0;
	int rc = 0;

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "Set rss flags command parameters: flow type = %d, data = %llu\n",
		   info->flow_type, info->data);

	switch (info->flow_type) {
	case TCP_V4_FLOW:
	case TCP_V6_FLOW:
		/* For TCP only 4-tuple hash is supported */
		if (info->data ^ (RXH_IP_SRC | RXH_IP_DST |
				  RXH_L4_B_0_1 | RXH_L4_B_2_3)) {
			DP_INFO(edev, "Command parameters not supported\n");
			return -EINVAL;
		}
		return 0;
	case UDP_V4_FLOW:
		/* For UDP either 2-tuple hash or 4-tuple hash is supported */
		if (info->data == (RXH_IP_SRC | RXH_IP_DST |
				   RXH_L4_B_0_1 | RXH_L4_B_2_3)) {
			set_caps = QED_RSS_IPV4_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple enabled\n");
		} else if (info->data == (RXH_IP_SRC | RXH_IP_DST)) {
			clr_caps = QED_RSS_IPV4_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple disabled\n");
		} else {
			return -EINVAL;
		}
		break;
	case UDP_V6_FLOW:
		/* For UDP either 2-tuple hash or 4-tuple hash is supported */
		if (info->data == (RXH_IP_SRC | RXH_IP_DST |
				   RXH_L4_B_0_1 | RXH_L4_B_2_3)) {
			set_caps = QED_RSS_IPV6_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple enabled\n");
		} else if (info->data == (RXH_IP_SRC | RXH_IP_DST)) {
			clr_caps = QED_RSS_IPV6_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple disabled\n");
		} else {
			return -EINVAL;
		}
		break;
	case IPV4_FLOW:
	case IPV6_FLOW:
		/* For IP only 2-tuple hash is supported */
		if (info->data ^ (RXH_IP_SRC | RXH_IP_DST)) {
			DP_INFO(edev, "Command parameters not supported\n");
			return -EINVAL;
		}
		return 0;
	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case SCTP_V6_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case IP_USER_FLOW:
	case ETHER_FLOW:
		/* RSS is not supported for these protocols */
		if (info->data) {
			DP_INFO(edev, "Command parameters not supported\n");
			return -EINVAL;
		}
		return 0;
	default:
		return -EINVAL;
	}

	/* No action is needed if there is no change in the rss capability */
	if (edev->rss_caps == ((edev->rss_caps & ~clr_caps) | set_caps))
		return 0;

	/* Update internal configuration */
	edev->rss_caps = ((edev->rss_caps & ~clr_caps) | set_caps);
	edev->rss_params_inited |= QEDE_RSS_CAPS_INITED;

	/* Re-configure if possible */
	__qede_lock(edev);
	if (edev->state == QEDE_STATE_OPEN) {
		vport_update_params = vzalloc(sizeof(*vport_update_params));
		if (!vport_update_params) {
			__qede_unlock(edev);
			return -ENOMEM;
		}
		qede_fill_rss_params(edev, &vport_update_params->rss_params,
				     &vport_update_params->update_rss_flg);
		rc = edev->ops->vport_update(edev->cdev, vport_update_params);
		vfree(vport_update_params);
	}
	__qede_unlock(edev);

	return rc;
}