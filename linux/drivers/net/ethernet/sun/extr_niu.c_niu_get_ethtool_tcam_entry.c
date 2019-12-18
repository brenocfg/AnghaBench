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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct niu_tcam_entry {int* key; int assoc_data; int /*<<< orphan*/  valid; } ;
struct niu_parent {int /*<<< orphan*/  index; struct niu_tcam_entry* tcam; } ;
struct niu {int /*<<< orphan*/  dev; struct niu_parent* parent; } ;
struct ethtool_rx_flow_spec {int flow_type; int ring_cookie; scalar_t__ location; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  data; struct ethtool_rx_flow_spec fs; } ;

/* Variables and functions */
#define  AH_V4_FLOW 138 
#define  AH_V6_FLOW 137 
 int EINVAL ; 
#define  ESP_V4_FLOW 136 
#define  ESP_V6_FLOW 135 
 scalar_t__ IPPROTO_ESP ; 
#define  IP_USER_FLOW 134 
 int RX_CLS_FLOW_DISC ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
 int TCAM_ASSOCDATA_DISC ; 
 int TCAM_ASSOCDATA_OFFSET ; 
 int TCAM_ASSOCDATA_OFFSET_SHIFT ; 
 int TCAM_V4KEY0_CLASS_CODE ; 
 int TCAM_V4KEY0_CLASS_CODE_SHIFT ; 
 scalar_t__ TCAM_V4KEY2_PROTO ; 
 scalar_t__ TCAM_V4KEY2_PROTO_SHIFT ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int niu_class_to_ethflow (int,int*) ; 
 int /*<<< orphan*/  niu_get_ip4fs_from_tcam_key (struct niu_tcam_entry*,struct ethtool_rx_flow_spec*) ; 
 size_t tcam_get_index (struct niu*,size_t) ; 
 int /*<<< orphan*/  tcam_get_size (struct niu*) ; 

__attribute__((used)) static int niu_get_ethtool_tcam_entry(struct niu *np,
				      struct ethtool_rxnfc *nfc)
{
	struct niu_parent *parent = np->parent;
	struct niu_tcam_entry *tp;
	struct ethtool_rx_flow_spec *fsp = &nfc->fs;
	u16 idx;
	u64 class;
	int ret = 0;

	idx = tcam_get_index(np, (u16)nfc->fs.location);

	tp = &parent->tcam[idx];
	if (!tp->valid) {
		netdev_info(np->dev, "niu%d: entry [%d] invalid for idx[%d]\n",
			    parent->index, (u16)nfc->fs.location, idx);
		return -EINVAL;
	}

	/* fill the flow spec entry */
	class = (tp->key[0] & TCAM_V4KEY0_CLASS_CODE) >>
		TCAM_V4KEY0_CLASS_CODE_SHIFT;
	ret = niu_class_to_ethflow(class, &fsp->flow_type);
	if (ret < 0) {
		netdev_info(np->dev, "niu%d: niu_class_to_ethflow failed\n",
			    parent->index);
		goto out;
	}

	if (fsp->flow_type == AH_V4_FLOW || fsp->flow_type == AH_V6_FLOW) {
		u32 proto = (tp->key[2] & TCAM_V4KEY2_PROTO) >>
			TCAM_V4KEY2_PROTO_SHIFT;
		if (proto == IPPROTO_ESP) {
			if (fsp->flow_type == AH_V4_FLOW)
				fsp->flow_type = ESP_V4_FLOW;
			else
				fsp->flow_type = ESP_V6_FLOW;
		}
	}

	switch (fsp->flow_type) {
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
	case SCTP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
		niu_get_ip4fs_from_tcam_key(tp, fsp);
		break;
	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
	case SCTP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
		/* Not yet implemented */
		ret = -EINVAL;
		break;
	case IP_USER_FLOW:
		niu_get_ip4fs_from_tcam_key(tp, fsp);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret < 0)
		goto out;

	if (tp->assoc_data & TCAM_ASSOCDATA_DISC)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
	else
		fsp->ring_cookie = (tp->assoc_data & TCAM_ASSOCDATA_OFFSET) >>
			TCAM_ASSOCDATA_OFFSET_SHIFT;

	/* put the tcam size here */
	nfc->data = tcam_get_size(np);
out:
	return ret;
}