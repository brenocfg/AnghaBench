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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; scalar_t__ cb; } ;
struct rtw_c2h_cmd {int /*<<< orphan*/ * payload; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *get_payload_from_coex_resp(struct sk_buff *resp)
{
	struct rtw_c2h_cmd *c2h;
	u32 pkt_offset;

	pkt_offset = *((u32 *)resp->cb);
	c2h = (struct rtw_c2h_cmd *)(resp->data + pkt_offset);

	return c2h->payload;
}