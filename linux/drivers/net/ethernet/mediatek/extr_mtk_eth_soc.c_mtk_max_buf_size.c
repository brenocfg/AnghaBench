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
struct skb_shared_info {int dummy; } ;

/* Variables and functions */
 int MTK_MAX_RX_LENGTH ; 
 int NET_IP_ALIGN ; 
 int NET_SKB_PAD ; 
 int SKB_DATA_ALIGN (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline int mtk_max_buf_size(int frag_size)
{
	int buf_size = frag_size - NET_SKB_PAD - NET_IP_ALIGN -
		       SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

	WARN_ON(buf_size < MTK_MAX_RX_LENGTH);

	return buf_size;
}