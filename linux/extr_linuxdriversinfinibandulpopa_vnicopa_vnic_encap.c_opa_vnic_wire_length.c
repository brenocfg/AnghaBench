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
typedef  int u32 ;
struct sk_buff {int len; } ;

/* Variables and functions */
 int OPA_VNIC_ICRC_TAIL_LEN ; 

__attribute__((used)) static inline int opa_vnic_wire_length(struct sk_buff *skb)
{
	u32 pad_len;

	/* padding for 8 bytes size alignment */
	pad_len = -(skb->len + OPA_VNIC_ICRC_TAIL_LEN) & 0x7;
	pad_len += OPA_VNIC_ICRC_TAIL_LEN;

	return (skb->len + pad_len) >> 3;
}