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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct dpaa2_fd {int dummy; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  buf_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_RAW_SIZE ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fd_get_len (struct dpaa2_fd const*) ; 
 int /*<<< orphan*/  dpaa2_fd_get_offset (struct dpaa2_fd const*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *build_linear_skb(struct dpaa2_eth_channel *ch,
					const struct dpaa2_fd *fd,
					void *fd_vaddr)
{
	struct sk_buff *skb = NULL;
	u16 fd_offset = dpaa2_fd_get_offset(fd);
	u32 fd_length = dpaa2_fd_get_len(fd);

	ch->buf_count--;

	skb = build_skb(fd_vaddr, DPAA2_ETH_RX_BUF_RAW_SIZE);
	if (unlikely(!skb))
		return NULL;

	skb_reserve(skb, fd_offset);
	skb_put(skb, fd_length);

	return skb;
}