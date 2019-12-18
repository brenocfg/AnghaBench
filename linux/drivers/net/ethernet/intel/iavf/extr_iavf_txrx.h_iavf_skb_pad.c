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

/* Variables and functions */
 scalar_t__ IAVF_2K_TOO_SMALL_WITH_PADDING ; 
 int IAVF_RXBUFFER_1536 ; 
 int IAVF_RXBUFFER_3072 ; 
 scalar_t__ NET_IP_ALIGN ; 
 int SKB_DATA_ALIGN (scalar_t__) ; 
 int iavf_compute_pad (int) ; 

__attribute__((used)) static inline int iavf_skb_pad(void)
{
	int rx_buf_len;

	/* If a 2K buffer cannot handle a standard Ethernet frame then
	 * optimize padding for a 3K buffer instead of a 1.5K buffer.
	 *
	 * For a 3K buffer we need to add enough padding to allow for
	 * tailroom due to NET_IP_ALIGN possibly shifting us out of
	 * cache-line alignment.
	 */
	if (IAVF_2K_TOO_SMALL_WITH_PADDING)
		rx_buf_len = IAVF_RXBUFFER_3072 + SKB_DATA_ALIGN(NET_IP_ALIGN);
	else
		rx_buf_len = IAVF_RXBUFFER_1536;

	/* if needed make room for NET_IP_ALIGN */
	rx_buf_len -= NET_IP_ALIGN;

	return iavf_compute_pad(rx_buf_len);
}