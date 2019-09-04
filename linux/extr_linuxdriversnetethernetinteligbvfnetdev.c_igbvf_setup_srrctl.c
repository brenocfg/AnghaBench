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
typedef  int u32 ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {int rx_buffer_len; int rx_ps_hdr_size; struct e1000_hw hw; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int E1000_SRRCTL_BSIZEHDRSIZE_SHIFT ; 
 int E1000_SRRCTL_BSIZEHDR_MASK ; 
 int E1000_SRRCTL_BSIZEPKT_MASK ; 
 int E1000_SRRCTL_BSIZEPKT_SHIFT ; 
 int E1000_SRRCTL_DESCTYPE_ADV_ONEBUF ; 
 int E1000_SRRCTL_DESCTYPE_HDR_SPLIT_ALWAYS ; 
 int E1000_SRRCTL_DESCTYPE_MASK ; 
 int E1000_SRRCTL_DROP_EN ; 
 int /*<<< orphan*/  SRRCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igbvf_setup_srrctl(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 srrctl = 0;

	srrctl &= ~(E1000_SRRCTL_DESCTYPE_MASK |
		    E1000_SRRCTL_BSIZEHDR_MASK |
		    E1000_SRRCTL_BSIZEPKT_MASK);

	/* Enable queue drop to avoid head of line blocking */
	srrctl |= E1000_SRRCTL_DROP_EN;

	/* Setup buffer sizes */
	srrctl |= ALIGN(adapter->rx_buffer_len, 1024) >>
		  E1000_SRRCTL_BSIZEPKT_SHIFT;

	if (adapter->rx_buffer_len < 2048) {
		adapter->rx_ps_hdr_size = 0;
		srrctl |= E1000_SRRCTL_DESCTYPE_ADV_ONEBUF;
	} else {
		adapter->rx_ps_hdr_size = 128;
		srrctl |= adapter->rx_ps_hdr_size <<
			  E1000_SRRCTL_BSIZEHDRSIZE_SHIFT;
		srrctl |= E1000_SRRCTL_DESCTYPE_HDR_SPLIT_ALWAYS;
	}

	ew32(SRRCTL(0), srrctl);
}