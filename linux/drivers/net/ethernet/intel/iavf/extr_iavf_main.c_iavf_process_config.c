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
struct virtchnl_vf_resource {int num_vsis; int vf_cap_flags; int /*<<< orphan*/  rss_lut_size; int /*<<< orphan*/  rss_key_size; TYPE_2__* vsi_res; } ;
struct net_device {int gso_partial_features; int hw_enc_features; int vlan_features; int hw_features; int features; int wanted_features; int mtu; int /*<<< orphan*/  priv_flags; } ;
struct iavf_vsi {int base_vector; int /*<<< orphan*/  qs_handle; struct net_device* netdev; int /*<<< orphan*/  work_limit; struct iavf_adapter* back; int /*<<< orphan*/  id; } ;
struct iavf_adapter {int num_req_queues; int /*<<< orphan*/  rss_lut_size; int /*<<< orphan*/  rss_key_size; TYPE_2__* vsi_res; struct net_device* netdev; struct iavf_vsi vsi; int /*<<< orphan*/  flags; TYPE_1__* pdev; struct virtchnl_vf_resource* vf_res; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {scalar_t__ vsi_type; int num_queue_pairs; int /*<<< orphan*/  qset_handle; int /*<<< orphan*/  vsi_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IAVF_DEFAULT_IRQ_WORK ; 
 int /*<<< orphan*/  IAVF_FLAG_REINIT_ITR_NEEDED ; 
 int /*<<< orphan*/  IAVF_HKEY_ARRAY_SIZE ; 
 int /*<<< orphan*/  IAVF_HLUT_ARRAY_SIZE ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int NETIF_F_GRO ; 
 int NETIF_F_GSO ; 
 int NETIF_F_GSO_GRE ; 
 int NETIF_F_GSO_GRE_CSUM ; 
 int NETIF_F_GSO_IPXIP4 ; 
 int NETIF_F_GSO_IPXIP6 ; 
 int NETIF_F_GSO_PARTIAL ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_GSO_UDP_TUNNEL_CSUM ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_TC ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SCTP_CRC ; 
 int NETIF_F_SG ; 
 int NETIF_F_SOFT_FEATURES ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_F_TSO_ECN ; 
 int NETIF_F_TSO_MANGLEID ; 
 int VIRTCHNL_VF_OFFLOAD_ADQ ; 
 int VIRTCHNL_VF_OFFLOAD_ENCAP ; 
 int VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_PF ; 
 int VIRTCHNL_VF_OFFLOAD_VLAN ; 
 scalar_t__ VIRTCHNL_VSI_SRIOV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  iavf_schedule_reset (struct iavf_adapter*) ; 

int iavf_process_config(struct iavf_adapter *adapter)
{
	struct virtchnl_vf_resource *vfres = adapter->vf_res;
	int i, num_req_queues = adapter->num_req_queues;
	struct net_device *netdev = adapter->netdev;
	struct iavf_vsi *vsi = &adapter->vsi;
	netdev_features_t hw_enc_features;
	netdev_features_t hw_features;

	/* got VF config message back from PF, now we can parse it */
	for (i = 0; i < vfres->num_vsis; i++) {
		if (vfres->vsi_res[i].vsi_type == VIRTCHNL_VSI_SRIOV)
			adapter->vsi_res = &vfres->vsi_res[i];
	}
	if (!adapter->vsi_res) {
		dev_err(&adapter->pdev->dev, "No LAN VSI found\n");
		return -ENODEV;
	}

	if (num_req_queues &&
	    num_req_queues != adapter->vsi_res->num_queue_pairs) {
		/* Problem.  The PF gave us fewer queues than what we had
		 * negotiated in our request.  Need a reset to see if we can't
		 * get back to a working state.
		 */
		dev_err(&adapter->pdev->dev,
			"Requested %d queues, but PF only gave us %d.\n",
			num_req_queues,
			adapter->vsi_res->num_queue_pairs);
		adapter->flags |= IAVF_FLAG_REINIT_ITR_NEEDED;
		adapter->num_req_queues = adapter->vsi_res->num_queue_pairs;
		iavf_schedule_reset(adapter);
		return -ENODEV;
	}
	adapter->num_req_queues = 0;

	hw_enc_features = NETIF_F_SG			|
			  NETIF_F_IP_CSUM		|
			  NETIF_F_IPV6_CSUM		|
			  NETIF_F_HIGHDMA		|
			  NETIF_F_SOFT_FEATURES	|
			  NETIF_F_TSO			|
			  NETIF_F_TSO_ECN		|
			  NETIF_F_TSO6			|
			  NETIF_F_SCTP_CRC		|
			  NETIF_F_RXHASH		|
			  NETIF_F_RXCSUM		|
			  0;

	/* advertise to stack only if offloads for encapsulated packets is
	 * supported
	 */
	if (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ENCAP) {
		hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL	|
				   NETIF_F_GSO_GRE		|
				   NETIF_F_GSO_GRE_CSUM		|
				   NETIF_F_GSO_IPXIP4		|
				   NETIF_F_GSO_IPXIP6		|
				   NETIF_F_GSO_UDP_TUNNEL_CSUM	|
				   NETIF_F_GSO_PARTIAL		|
				   0;

		if (!(vfres->vf_cap_flags &
		      VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM))
			netdev->gso_partial_features |=
				NETIF_F_GSO_UDP_TUNNEL_CSUM;

		netdev->gso_partial_features |= NETIF_F_GSO_GRE_CSUM;
		netdev->hw_enc_features |= NETIF_F_TSO_MANGLEID;
		netdev->hw_enc_features |= hw_enc_features;
	}
	/* record features VLANs can make use of */
	netdev->vlan_features |= hw_enc_features | NETIF_F_TSO_MANGLEID;

	/* Write features and hw_features separately to avoid polluting
	 * with, or dropping, features that are set when we registered.
	 */
	hw_features = hw_enc_features;

	/* Enable VLAN features if supported */
	if (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_VLAN)
		hw_features |= (NETIF_F_HW_VLAN_CTAG_TX |
				NETIF_F_HW_VLAN_CTAG_RX);
	/* Enable cloud filter if ADQ is supported */
	if (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ)
		hw_features |= NETIF_F_HW_TC;

	netdev->hw_features |= hw_features;

	netdev->features |= hw_features;

	if (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_VLAN)
		netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* Do not turn on offloads when they are requested to be turned off.
	 * TSO needs minimum 576 bytes to work correctly.
	 */
	if (netdev->wanted_features) {
		if (!(netdev->wanted_features & NETIF_F_TSO) ||
		    netdev->mtu < 576)
			netdev->features &= ~NETIF_F_TSO;
		if (!(netdev->wanted_features & NETIF_F_TSO6) ||
		    netdev->mtu < 576)
			netdev->features &= ~NETIF_F_TSO6;
		if (!(netdev->wanted_features & NETIF_F_TSO_ECN))
			netdev->features &= ~NETIF_F_TSO_ECN;
		if (!(netdev->wanted_features & NETIF_F_GRO))
			netdev->features &= ~NETIF_F_GRO;
		if (!(netdev->wanted_features & NETIF_F_GSO))
			netdev->features &= ~NETIF_F_GSO;
	}

	adapter->vsi.id = adapter->vsi_res->vsi_id;

	adapter->vsi.back = adapter;
	adapter->vsi.base_vector = 1;
	adapter->vsi.work_limit = IAVF_DEFAULT_IRQ_WORK;
	vsi->netdev = adapter->netdev;
	vsi->qs_handle = adapter->vsi_res->qset_handle;
	if (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_RSS_PF) {
		adapter->rss_key_size = vfres->rss_key_size;
		adapter->rss_lut_size = vfres->rss_lut_size;
	} else {
		adapter->rss_key_size = IAVF_HKEY_ARRAY_SIZE;
		adapter->rss_lut_size = IAVF_HLUT_ARRAY_SIZE;
	}

	return 0;
}