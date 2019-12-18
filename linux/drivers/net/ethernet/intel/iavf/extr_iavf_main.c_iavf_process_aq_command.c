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
struct iavf_adapter {int aq_required; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FLAG_VF_MULTICAST_PROMISC ; 
 int FLAG_VF_UNICAST_PROMISC ; 
 int IAVF_FLAG_AQ_ADD_CLOUD_FILTER ; 
 int IAVF_FLAG_AQ_ADD_MAC_FILTER ; 
 int IAVF_FLAG_AQ_ADD_VLAN_FILTER ; 
 int IAVF_FLAG_AQ_CONFIGURE_QUEUES ; 
 int IAVF_FLAG_AQ_CONFIGURE_RSS ; 
 int IAVF_FLAG_AQ_DEL_CLOUD_FILTER ; 
 int IAVF_FLAG_AQ_DEL_MAC_FILTER ; 
 int IAVF_FLAG_AQ_DEL_VLAN_FILTER ; 
 int IAVF_FLAG_AQ_DISABLE_CHANNELS ; 
 int IAVF_FLAG_AQ_DISABLE_QUEUES ; 
 int IAVF_FLAG_AQ_DISABLE_VLAN_STRIPPING ; 
 int IAVF_FLAG_AQ_ENABLE_CHANNELS ; 
 int IAVF_FLAG_AQ_ENABLE_QUEUES ; 
 int IAVF_FLAG_AQ_ENABLE_VLAN_STRIPPING ; 
 int IAVF_FLAG_AQ_GET_CONFIG ; 
 int IAVF_FLAG_AQ_GET_HENA ; 
 int IAVF_FLAG_AQ_MAP_VECTORS ; 
 int IAVF_FLAG_AQ_RELEASE_ALLMULTI ; 
 int IAVF_FLAG_AQ_RELEASE_PROMISC ; 
 int IAVF_FLAG_AQ_REQUEST_ALLMULTI ; 
 int IAVF_FLAG_AQ_REQUEST_PROMISC ; 
 int IAVF_FLAG_AQ_SET_HENA ; 
 int IAVF_FLAG_AQ_SET_RSS_KEY ; 
 int IAVF_FLAG_AQ_SET_RSS_LUT ; 
 int /*<<< orphan*/  iavf_add_cloud_filter (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_add_ether_addrs (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_add_vlans (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_configure_queues (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_del_cloud_filter (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_del_ether_addrs (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_del_vlans (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_disable_channels (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_disable_queues (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_disable_vlan_stripping (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_enable_channels (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_enable_queues (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_enable_vlan_stripping (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_get_hena (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_map_queues (struct iavf_adapter*) ; 
 int iavf_send_vf_config_msg (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_set_hena (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_set_promiscuous (struct iavf_adapter*,int) ; 
 int /*<<< orphan*/  iavf_set_rss_key (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_set_rss_lut (struct iavf_adapter*) ; 

__attribute__((used)) static int iavf_process_aq_command(struct iavf_adapter *adapter)
{
	if (adapter->aq_required & IAVF_FLAG_AQ_GET_CONFIG)
		return iavf_send_vf_config_msg(adapter);
	if (adapter->aq_required & IAVF_FLAG_AQ_DISABLE_QUEUES) {
		iavf_disable_queues(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_MAP_VECTORS) {
		iavf_map_queues(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_ADD_MAC_FILTER) {
		iavf_add_ether_addrs(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_ADD_VLAN_FILTER) {
		iavf_add_vlans(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_DEL_MAC_FILTER) {
		iavf_del_ether_addrs(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_DEL_VLAN_FILTER) {
		iavf_del_vlans(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_ENABLE_VLAN_STRIPPING) {
		iavf_enable_vlan_stripping(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_DISABLE_VLAN_STRIPPING) {
		iavf_disable_vlan_stripping(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_CONFIGURE_QUEUES) {
		iavf_configure_queues(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_ENABLE_QUEUES) {
		iavf_enable_queues(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_CONFIGURE_RSS) {
		/* This message goes straight to the firmware, not the
		 * PF, so we don't have to set current_op as we will
		 * not get a response through the ARQ.
		 */
		adapter->aq_required &= ~IAVF_FLAG_AQ_CONFIGURE_RSS;
		return 0;
	}
	if (adapter->aq_required & IAVF_FLAG_AQ_GET_HENA) {
		iavf_get_hena(adapter);
		return 0;
	}
	if (adapter->aq_required & IAVF_FLAG_AQ_SET_HENA) {
		iavf_set_hena(adapter);
		return 0;
	}
	if (adapter->aq_required & IAVF_FLAG_AQ_SET_RSS_KEY) {
		iavf_set_rss_key(adapter);
		return 0;
	}
	if (adapter->aq_required & IAVF_FLAG_AQ_SET_RSS_LUT) {
		iavf_set_rss_lut(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_REQUEST_PROMISC) {
		iavf_set_promiscuous(adapter, FLAG_VF_UNICAST_PROMISC |
				       FLAG_VF_MULTICAST_PROMISC);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_REQUEST_ALLMULTI) {
		iavf_set_promiscuous(adapter, FLAG_VF_MULTICAST_PROMISC);
		return 0;
	}

	if ((adapter->aq_required & IAVF_FLAG_AQ_RELEASE_PROMISC) &&
	    (adapter->aq_required & IAVF_FLAG_AQ_RELEASE_ALLMULTI)) {
		iavf_set_promiscuous(adapter, 0);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_ENABLE_CHANNELS) {
		iavf_enable_channels(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_DISABLE_CHANNELS) {
		iavf_disable_channels(adapter);
		return 0;
	}
	if (adapter->aq_required & IAVF_FLAG_AQ_ADD_CLOUD_FILTER) {
		iavf_add_cloud_filter(adapter);
		return 0;
	}

	if (adapter->aq_required & IAVF_FLAG_AQ_DEL_CLOUD_FILTER) {
		iavf_del_cloud_filter(adapter);
		return 0;
	}
	if (adapter->aq_required & IAVF_FLAG_AQ_DEL_CLOUD_FILTER) {
		iavf_del_cloud_filter(adapter);
		return 0;
	}
	if (adapter->aq_required & IAVF_FLAG_AQ_ADD_CLOUD_FILTER) {
		iavf_add_cloud_filter(adapter);
		return 0;
	}
	return -EAGAIN;
}