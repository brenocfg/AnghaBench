#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int chained_metadata_format; int /*<<< orphan*/  netdev; scalar_t__ rx_offset; } ;
struct TYPE_5__ {int major; } ;
struct nfp_net {int cap; TYPE_4__* app; TYPE_2__ dp; TYPE_1__ fw_ver; void* max_mtu; } ;
struct TYPE_8__ {TYPE_3__* type; } ;
struct TYPE_7__ {int ctrl_cap_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NFP_NET_CFG_CAP ; 
 int NFP_NET_CFG_CTRL_CHAIN_META ; 
 int NFP_NET_CFG_CTRL_RSS ; 
 int /*<<< orphan*/  NFP_NET_CFG_MAX_MTU ; 
 int /*<<< orphan*/  NFP_NET_CFG_RX_OFFSET ; 
 scalar_t__ NFP_NET_MAX_PREPEND ; 
 scalar_t__ NFP_NET_RX_OFFSET ; 
 int /*<<< orphan*/  nn_err (struct nfp_net*,char*,scalar_t__) ; 
 void* nn_readl (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_net_read_caps(struct nfp_net *nn)
{
	/* Get some of the read-only fields from the BAR */
	nn->cap = nn_readl(nn, NFP_NET_CFG_CAP);
	nn->max_mtu = nn_readl(nn, NFP_NET_CFG_MAX_MTU);

	/* ABI 4.x and ctrl vNIC always use chained metadata, in other cases
	 * we allow use of non-chained metadata if RSS(v1) is the only
	 * advertised capability requiring metadata.
	 */
	nn->dp.chained_metadata_format = nn->fw_ver.major == 4 ||
					 !nn->dp.netdev ||
					 !(nn->cap & NFP_NET_CFG_CTRL_RSS) ||
					 nn->cap & NFP_NET_CFG_CTRL_CHAIN_META;
	/* RSS(v1) uses non-chained metadata format, except in ABI 4.x where
	 * it has the same meaning as RSSv2.
	 */
	if (nn->dp.chained_metadata_format && nn->fw_ver.major != 4)
		nn->cap &= ~NFP_NET_CFG_CTRL_RSS;

	/* Determine RX packet/metadata boundary offset */
	if (nn->fw_ver.major >= 2) {
		u32 reg;

		reg = nn_readl(nn, NFP_NET_CFG_RX_OFFSET);
		if (reg > NFP_NET_MAX_PREPEND) {
			nn_err(nn, "Invalid rx offset: %d\n", reg);
			return -EINVAL;
		}
		nn->dp.rx_offset = reg;
	} else {
		nn->dp.rx_offset = NFP_NET_RX_OFFSET;
	}

	/* For control vNICs mask out the capabilities app doesn't want. */
	if (!nn->dp.netdev)
		nn->cap &= nn->app->type->ctrl_cap_mask;

	return 0;
}