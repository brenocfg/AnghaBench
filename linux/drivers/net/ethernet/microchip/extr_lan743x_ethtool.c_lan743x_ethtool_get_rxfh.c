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
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  RFE_HASH_KEY (int) ; 
 int /*<<< orphan*/  RFE_INDX (int) ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int lan743x_ethtool_get_rxfh(struct net_device *netdev,
				    u32 *indir, u8 *key, u8 *hfunc)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);

	if (indir) {
		int dw_index;
		int byte_index = 0;

		for (dw_index = 0; dw_index < 32; dw_index++) {
			u32 four_entries =
				lan743x_csr_read(adapter, RFE_INDX(dw_index));

			byte_index = dw_index << 2;
			indir[byte_index + 0] =
				((four_entries >> 0) & 0x000000FF);
			indir[byte_index + 1] =
				((four_entries >> 8) & 0x000000FF);
			indir[byte_index + 2] =
				((four_entries >> 16) & 0x000000FF);
			indir[byte_index + 3] =
				((four_entries >> 24) & 0x000000FF);
		}
	}
	if (key) {
		int dword_index;
		int byte_index = 0;

		for (dword_index = 0; dword_index < 10; dword_index++) {
			u32 four_entries =
				lan743x_csr_read(adapter,
						 RFE_HASH_KEY(dword_index));

			byte_index = dword_index << 2;
			key[byte_index + 0] =
				((four_entries >> 0) & 0x000000FF);
			key[byte_index + 1] =
				((four_entries >> 8) & 0x000000FF);
			key[byte_index + 2] =
				((four_entries >> 16) & 0x000000FF);
			key[byte_index + 3] =
				((four_entries >> 24) & 0x000000FF);
		}
	}
	if (hfunc)
		(*hfunc) = ETH_RSS_HASH_TOP;
	return 0;
}