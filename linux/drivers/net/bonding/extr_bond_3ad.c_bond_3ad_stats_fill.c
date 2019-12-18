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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct bond_3ad_stats {int /*<<< orphan*/  marker_unknown_rx; int /*<<< orphan*/  marker_resp_tx; int /*<<< orphan*/  marker_resp_rx; int /*<<< orphan*/  marker_tx; int /*<<< orphan*/  marker_rx; int /*<<< orphan*/  lacpdu_illegal_rx; int /*<<< orphan*/  lacpdu_unknown_rx; int /*<<< orphan*/  lacpdu_tx; int /*<<< orphan*/  lacpdu_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_3AD_STAT_LACPDU_ILLEGAL_RX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_LACPDU_RX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_LACPDU_TX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_LACPDU_UNKNOWN_RX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_MARKER_RESP_RX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_MARKER_RESP_TX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_MARKER_RX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_MARKER_TX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_MARKER_UNKNOWN_RX ; 
 int /*<<< orphan*/  BOND_3AD_STAT_PAD ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bond_3ad_stats_fill(struct sk_buff *skb, struct bond_3ad_stats *stats)
{
	u64 val;

	val = atomic64_read(&stats->lacpdu_rx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_RX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;
	val = atomic64_read(&stats->lacpdu_tx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_TX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;
	val = atomic64_read(&stats->lacpdu_unknown_rx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_UNKNOWN_RX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;
	val = atomic64_read(&stats->lacpdu_illegal_rx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_ILLEGAL_RX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;

	val = atomic64_read(&stats->marker_rx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_RX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;
	val = atomic64_read(&stats->marker_tx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_TX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;
	val = atomic64_read(&stats->marker_resp_rx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_RESP_RX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;
	val = atomic64_read(&stats->marker_resp_tx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_RESP_TX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;
	val = atomic64_read(&stats->marker_unknown_rx);
	if (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_UNKNOWN_RX, val,
			      BOND_3AD_STAT_PAD))
		return -EMSGSIZE;

	return 0;
}