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
typedef  int /*<<< orphan*/  u32 ;
struct iavf_hw {int dummy; } ;
struct iavf_adapter {int hena; int /*<<< orphan*/  rss_key_size; scalar_t__ rss_key; TYPE_1__* vf_res; struct iavf_hw hw; } ;
struct TYPE_2__ {int vf_cap_flags; } ;

/* Variables and functions */
 int IAVF_DEFAULT_RSS_HENA ; 
 int IAVF_DEFAULT_RSS_HENA_EXPANDED ; 
 int /*<<< orphan*/  IAVF_VFQF_HENA (int) ; 
 int /*<<< orphan*/  RSS_PF (struct iavf_adapter*) ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2 ; 
 int iavf_config_rss (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_fill_rss_lut (struct iavf_adapter*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct iavf_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iavf_init_rss(struct iavf_adapter *adapter)
{
	struct iavf_hw *hw = &adapter->hw;
	int ret;

	if (!RSS_PF(adapter)) {
		/* Enable PCTYPES for RSS, TCP/UDP with IPv4/IPv6 */
		if (adapter->vf_res->vf_cap_flags &
		    VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2)
			adapter->hena = IAVF_DEFAULT_RSS_HENA_EXPANDED;
		else
			adapter->hena = IAVF_DEFAULT_RSS_HENA;

		wr32(hw, IAVF_VFQF_HENA(0), (u32)adapter->hena);
		wr32(hw, IAVF_VFQF_HENA(1), (u32)(adapter->hena >> 32));
	}

	iavf_fill_rss_lut(adapter);
	netdev_rss_key_fill((void *)adapter->rss_key, adapter->rss_key_size);
	ret = iavf_config_rss(adapter);

	return ret;
}