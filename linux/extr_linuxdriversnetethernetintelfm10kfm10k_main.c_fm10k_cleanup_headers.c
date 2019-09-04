#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int csum_err; } ;
union fm10k_rx_desc {TYPE_1__ w; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  errors; int /*<<< orphan*/  length_errors; int /*<<< orphan*/  link_errors; int /*<<< orphan*/  pp_errors; int /*<<< orphan*/  drops; int /*<<< orphan*/  switch_errors; } ;
struct fm10k_ring {TYPE_2__ rx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_RXD_ERR_NO_DESCRIPTOR ; 
 int /*<<< orphan*/  FM10K_RXD_ERR_PP_ERROR ; 
 int /*<<< orphan*/  FM10K_RXD_ERR_SWITCH_ERROR ; 
 int /*<<< orphan*/  FM10K_RXD_ERR_SWITCH_READY ; 
 int /*<<< orphan*/  FM10K_RXD_ERR_TOO_BIG ; 
 int /*<<< orphan*/  FM10K_RXD_STATUS_RXE ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ eth_skb_pad (struct sk_buff*) ; 
 int /*<<< orphan*/  fm10k_test_staterr (union fm10k_rx_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fm10k_cleanup_headers(struct fm10k_ring *rx_ring,
				  union fm10k_rx_desc *rx_desc,
				  struct sk_buff *skb)
{
	if (unlikely((fm10k_test_staterr(rx_desc,
					 FM10K_RXD_STATUS_RXE)))) {
#define FM10K_TEST_RXD_BIT(rxd, bit) \
	((rxd)->w.csum_err & cpu_to_le16(bit))
		if (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_SWITCH_ERROR))
			rx_ring->rx_stats.switch_errors++;
		if (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_NO_DESCRIPTOR))
			rx_ring->rx_stats.drops++;
		if (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_PP_ERROR))
			rx_ring->rx_stats.pp_errors++;
		if (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_SWITCH_READY))
			rx_ring->rx_stats.link_errors++;
		if (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_TOO_BIG))
			rx_ring->rx_stats.length_errors++;
		dev_kfree_skb_any(skb);
		rx_ring->rx_stats.errors++;
		return true;
	}

	/* if eth_skb_pad returns an error the skb was freed */
	if (eth_skb_pad(skb))
		return true;

	return false;
}