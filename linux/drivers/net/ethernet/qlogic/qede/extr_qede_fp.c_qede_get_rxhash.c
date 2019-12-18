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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
typedef  enum rss_hash_type { ____Placeholder_rss_hash_type } rss_hash_type ;
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_FAST_PATH_RX_REG_CQE_RSS_HASH_TYPE ; 
 int GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
 int PKT_HASH_TYPE_NONE ; 
 int RSS_HASH_TYPE_IPV4 ; 
 int RSS_HASH_TYPE_IPV6 ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qede_get_rxhash(struct sk_buff *skb, u8 bitfields, __le32 rss_hash)
{
	enum pkt_hash_types hash_type = PKT_HASH_TYPE_NONE;
	enum rss_hash_type htype;
	u32 hash = 0;

	htype = GET_FIELD(bitfields, ETH_FAST_PATH_RX_REG_CQE_RSS_HASH_TYPE);
	if (htype) {
		hash_type = ((htype == RSS_HASH_TYPE_IPV4) ||
			     (htype == RSS_HASH_TYPE_IPV6)) ?
			    PKT_HASH_TYPE_L3 : PKT_HASH_TYPE_L4;
		hash = le32_to_cpu(rss_hash);
	}
	skb_set_hash(skb, hash, hash_type);
}