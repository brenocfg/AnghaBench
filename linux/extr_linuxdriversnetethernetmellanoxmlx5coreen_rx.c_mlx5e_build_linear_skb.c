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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct mlx5e_rq {TYPE_1__* stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  buff_alloc_err; } ;

/* Variables and functions */
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline
struct sk_buff *mlx5e_build_linear_skb(struct mlx5e_rq *rq, void *va,
				       u32 frag_size, u16 headroom,
				       u32 cqe_bcnt)
{
	struct sk_buff *skb = build_skb(va, frag_size);

	if (unlikely(!skb)) {
		rq->stats->buff_alloc_err++;
		return NULL;
	}

	skb_reserve(skb, headroom);
	skb_put(skb, cqe_bcnt);

	return skb;
}