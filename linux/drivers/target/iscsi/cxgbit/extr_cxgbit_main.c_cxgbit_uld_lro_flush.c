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
struct t4_lro_mgr {int /*<<< orphan*/  lroq; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgbit_lro_flush (struct t4_lro_mgr*,struct sk_buff*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxgbit_uld_lro_flush(struct t4_lro_mgr *lro_mgr)
{
	struct sk_buff *skb;

	while ((skb = skb_peek(&lro_mgr->lroq)))
		cxgbit_lro_flush(lro_mgr, skb);
}