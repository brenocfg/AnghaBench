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
struct octeon_droq {TYPE_1__* recv_buf_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rbd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void octeon_fast_packet_next(struct octeon_droq *droq,
					   struct sk_buff *nicbuf,
					   int copy_len,
					   int idx)
{
	skb_put_data(nicbuf, get_rbd(droq->recv_buf_list[idx].buffer),
		     copy_len);
}