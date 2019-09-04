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
struct sk_buff {int dummy; } ;
struct nfp_flower_cmsg_lag_config {int /*<<< orphan*/  group_id; } ;
struct nfp_fl_lag {int /*<<< orphan*/  retrans_skbs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ NFP_FL_LAG_GROUP_MAX ; 
 scalar_t__ NFP_FL_LAG_RETRANS_LIMIT ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct nfp_flower_cmsg_lag_config* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_fl_lag_put_unprocessed(struct nfp_fl_lag *lag, struct sk_buff *skb)
{
	struct nfp_flower_cmsg_lag_config *cmsg_payload;

	cmsg_payload = nfp_flower_cmsg_get_data(skb);
	if (be32_to_cpu(cmsg_payload->group_id) >= NFP_FL_LAG_GROUP_MAX)
		return -EINVAL;

	/* Drop cmsg retrans if storage limit is exceeded to prevent
	 * overloading. If the fw notices that expected messages have not been
	 * received in a given time block, it will request a full resync.
	 */
	if (skb_queue_len(&lag->retrans_skbs) >= NFP_FL_LAG_RETRANS_LIMIT)
		return -ENOSPC;

	__skb_queue_tail(&lag->retrans_skbs, skb);

	return 0;
}