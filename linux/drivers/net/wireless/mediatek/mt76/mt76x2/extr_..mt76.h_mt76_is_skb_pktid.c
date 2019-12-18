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
typedef  int u8 ;

/* Variables and functions */
 int MT_PACKET_ID_FIRST ; 
 int MT_PACKET_ID_HAS_RATE ; 

__attribute__((used)) static inline bool mt76_is_skb_pktid(u8 pktid)
{
	if (pktid & MT_PACKET_ID_HAS_RATE)
		return false;

	return pktid >= MT_PACKET_ID_FIRST;
}