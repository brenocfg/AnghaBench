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
struct sk_buff {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  __get_unaligned_cpu32 (void const*) ; 
 void* skb_header_pointer (struct sk_buff const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 mlx5e_get_fcs(const struct sk_buff *skb)
{
	const void *fcs_bytes;
	u32 _fcs_bytes;

	fcs_bytes = skb_header_pointer(skb, skb->len - ETH_FCS_LEN,
				       ETH_FCS_LEN, &_fcs_bytes);

	return __get_unaligned_cpu32(fcs_bytes);
}