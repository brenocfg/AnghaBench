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
struct isac {scalar_t__ tx_cnt; int /*<<< orphan*/  tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_WARN ; 
 int /*<<< orphan*/  skb_push (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void isac_retransmit(struct isac *isac)
{
	if (!isac->tx_skb) {
		DBG(DBG_WARN, "no skb");
		return;
	}
	skb_push(isac->tx_skb, isac->tx_cnt);
	isac->tx_cnt = 0;
}