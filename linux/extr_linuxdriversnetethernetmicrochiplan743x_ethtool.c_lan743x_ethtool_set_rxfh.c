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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  RFE_HASH_KEY (int) ; 
 int /*<<< orphan*/  RFE_INDX (int) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int lan743x_ethtool_set_rxfh(struct net_device *netdev,
				    const u32 *indir, const u8 *key,
				    const u8 hfunc)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);

	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;

	if (indir) {
		u32 indir_value = 0;
		int dword_index = 0;
		int byte_index = 0;

		for (dword_index = 0; dword_index < 32; dword_index++) {
			byte_index = dword_index << 2;
			indir_value =
				(((indir[byte_index + 0] & 0x000000FF) << 0) |
				((indir[byte_index + 1] & 0x000000FF) << 8) |
				((indir[byte_index + 2] & 0x000000FF) << 16) |
				((indir[byte_index + 3] & 0x000000FF) << 24));
			lan743x_csr_write(adapter, RFE_INDX(dword_index),
					  indir_value);
		}
	}
	if (key) {
		int dword_index = 0;
		int byte_index = 0;
		u32 key_value = 0;

		for (dword_index = 0; dword_index < 10; dword_index++) {
			byte_index = dword_index << 2;
			key_value =
				((((u32)(key[byte_index + 0])) << 0) |
				(((u32)(key[byte_index + 1])) << 8) |
				(((u32)(key[byte_index + 2])) << 16) |
				(((u32)(key[byte_index + 3])) << 24));
			lan743x_csr_write(adapter, RFE_HASH_KEY(dword_index),
					  key_value);
		}
	}
	return 0;
}