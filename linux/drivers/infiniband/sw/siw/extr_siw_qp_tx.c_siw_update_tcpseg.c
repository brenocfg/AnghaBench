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
struct tcp_sock {int gso_segs; int mss_cache; } ;
struct socket {int /*<<< orphan*/  sk; } ;
struct siw_iwarp_tx {scalar_t__ gso_seg_limit; int tcp_seglen; } ;

/* Variables and functions */
 int min_t (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct tcp_sock* tcp_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static void siw_update_tcpseg(struct siw_iwarp_tx *c_tx,
				     struct socket *s)
{
	struct tcp_sock *tp = tcp_sk(s->sk);

	if (tp->gso_segs) {
		if (c_tx->gso_seg_limit == 0)
			c_tx->tcp_seglen = tp->mss_cache * tp->gso_segs;
		else
			c_tx->tcp_seglen =
				tp->mss_cache *
				min_t(u16, c_tx->gso_seg_limit, tp->gso_segs);
	} else {
		c_tx->tcp_seglen = tp->mss_cache;
	}
	/* Loopback may give odd numbers */
	c_tx->tcp_seglen &= 0xfffffff8;
}