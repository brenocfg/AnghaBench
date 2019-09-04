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
struct sk_buff {int dummy; } ;
struct chtls_sock {int /*<<< orphan*/  sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 scalar_t__ KEY_ON_MEM_SZ ; 
 int TLS_WR_CPL_LEN ; 
 scalar_t__ ivs_size (int /*<<< orphan*/ ,struct sk_buff const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_ulp_tls_iv_imm (struct sk_buff const*) ; 

__attribute__((used)) static int chtls_wr_size(struct chtls_sock *csk, const struct sk_buff *skb,
			 bool size)
{
	int wr_size;

	wr_size = TLS_WR_CPL_LEN;
	wr_size += KEY_ON_MEM_SZ;
	wr_size += ivs_size(csk->sk, skb);

	if (size)
		return wr_size;

	/* frags counted for IV dsgl */
	if (!skb_ulp_tls_iv_imm(skb))
		skb_shinfo(skb)->nr_frags++;

	return wr_size;
}