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
struct sk_buff {int priority; } ;

/* Variables and functions */
#define  RTW_TX_QUEUE_BCN 131 
#define  RTW_TX_QUEUE_H2C 130 
#define  RTW_TX_QUEUE_HI0 129 
#define  RTW_TX_QUEUE_MGMT 128 
 int TX_DESC_QSEL_BEACON ; 
 int TX_DESC_QSEL_H2C ; 
 int TX_DESC_QSEL_HIGH ; 
 int TX_DESC_QSEL_MGMT ; 

__attribute__((used)) static u8 rtw_pci_get_tx_qsel(struct sk_buff *skb, u8 queue)
{
	switch (queue) {
	case RTW_TX_QUEUE_BCN:
		return TX_DESC_QSEL_BEACON;
	case RTW_TX_QUEUE_H2C:
		return TX_DESC_QSEL_H2C;
	case RTW_TX_QUEUE_MGMT:
		return TX_DESC_QSEL_MGMT;
	case RTW_TX_QUEUE_HI0:
		return TX_DESC_QSEL_HIGH;
	default:
		return skb->priority;
	}
}