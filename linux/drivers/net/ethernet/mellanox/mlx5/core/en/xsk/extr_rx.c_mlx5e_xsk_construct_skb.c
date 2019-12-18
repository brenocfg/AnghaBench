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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;
struct mlx5e_rq {TYPE_2__* stats; TYPE_1__ cq; } ;
struct TYPE_4__ {int /*<<< orphan*/  buff_alloc_err; } ;

/* Variables and functions */
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *mlx5e_xsk_construct_skb(struct mlx5e_rq *rq, void *data,
					       u32 cqe_bcnt)
{
	struct sk_buff *skb;

	skb = napi_alloc_skb(rq->cq.napi, cqe_bcnt);
	if (unlikely(!skb)) {
		rq->stats->buff_alloc_err++;
		return NULL;
	}

	skb_put_data(skb, data, cqe_bcnt);

	return skb;
}