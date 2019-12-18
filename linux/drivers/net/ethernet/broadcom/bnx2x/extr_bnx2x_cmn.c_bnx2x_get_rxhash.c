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
struct eth_fast_path_rx_cqe {int status_flags; int /*<<< orphan*/  rss_hash_result; } ;
struct bnx2x {TYPE_1__* dev; } ;
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;
typedef  enum eth_rss_hash_type { ____Placeholder_eth_rss_hash_type } eth_rss_hash_type ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int ETH_FAST_PATH_RX_CQE_RSS_HASH_FLG ; 
 int ETH_FAST_PATH_RX_CQE_RSS_HASH_TYPE ; 
 int NETIF_F_RXHASH ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
 int PKT_HASH_TYPE_NONE ; 
 int TCP_IPV4_HASH_TYPE ; 
 int TCP_IPV6_HASH_TYPE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 bnx2x_get_rxhash(const struct bnx2x *bp,
			    const struct eth_fast_path_rx_cqe *cqe,
			    enum pkt_hash_types *rxhash_type)
{
	/* Get Toeplitz hash from CQE */
	if ((bp->dev->features & NETIF_F_RXHASH) &&
	    (cqe->status_flags & ETH_FAST_PATH_RX_CQE_RSS_HASH_FLG)) {
		enum eth_rss_hash_type htype;

		htype = cqe->status_flags & ETH_FAST_PATH_RX_CQE_RSS_HASH_TYPE;
		*rxhash_type = ((htype == TCP_IPV4_HASH_TYPE) ||
				(htype == TCP_IPV6_HASH_TYPE)) ?
			       PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3;

		return le32_to_cpu(cqe->rss_hash_result);
	}
	*rxhash_type = PKT_HASH_TYPE_NONE;
	return 0;
}