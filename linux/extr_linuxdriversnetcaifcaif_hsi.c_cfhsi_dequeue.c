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
struct sk_buff {int dummy; } ;
struct cfhsi {int /*<<< orphan*/ * qhead; } ;

/* Variables and functions */
 int CFHSI_PRIO_LAST ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *cfhsi_dequeue(struct cfhsi *cfhsi)
{
	struct sk_buff *skb;
	int i;

	for (i = 0; i < CFHSI_PRIO_LAST; ++i) {
		skb = skb_dequeue(&cfhsi->qhead[i]);
		if (skb)
			break;
	}

	return skb;
}