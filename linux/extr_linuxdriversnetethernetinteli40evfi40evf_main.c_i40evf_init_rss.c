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
struct i40e_hw {int dummy; } ;
struct i40evf_adapter {int hena; int /*<<< orphan*/  rss_key_size; scalar_t__ rss_key; TYPE_1__* vf_res; struct i40e_hw hw; } ;
struct TYPE_2__ {int vf_cap_flags; } ;

/* Variables and functions */
 int I40E_DEFAULT_RSS_HENA ; 
 int I40E_DEFAULT_RSS_HENA_EXPANDED ; 
 int /*<<< orphan*/  I40E_VFQF_HENA (int) ; 
 int /*<<< orphan*/  RSS_PF (struct i40evf_adapter*) ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2 ; 
 int i40evf_config_rss (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_fill_rss_lut (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40evf_init_rss(struct i40evf_adapter *adapter)
{
	struct i40e_hw *hw = &adapter->hw;
	int ret;

	if (!RSS_PF(adapter)) {
		/* Enable PCTYPES for RSS, TCP/UDP with IPv4/IPv6 */
		if (adapter->vf_res->vf_cap_flags &
		    VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2)
			adapter->hena = I40E_DEFAULT_RSS_HENA_EXPANDED;
		else
			adapter->hena = I40E_DEFAULT_RSS_HENA;

		wr32(hw, I40E_VFQF_HENA(0), (u32)adapter->hena);
		wr32(hw, I40E_VFQF_HENA(1), (u32)(adapter->hena >> 32));
	}

	i40evf_fill_rss_lut(adapter);

	netdev_rss_key_fill((void *)adapter->rss_key, adapter->rss_key_size);
	ret = i40evf_config_rss(adapter);

	return ret;
}