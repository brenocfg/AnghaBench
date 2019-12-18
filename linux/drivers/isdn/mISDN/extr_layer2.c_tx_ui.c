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
typedef  int u_char ;
struct sk_buff {int dummy; } ;
struct layer2 {int /*<<< orphan*/  ui_queue; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  FLG_LAPD_NET ; 
 int MAX_L2HEADER_LEN ; 
 int UI ; 
 int /*<<< orphan*/  enqueue_ui (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int sethdraddr (struct layer2*,int*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tx_ui(struct layer2 *l2)
{
	struct sk_buff *skb;
	u_char header[MAX_L2HEADER_LEN];
	int i;

	i = sethdraddr(l2, header, CMD);
	if (test_bit(FLG_LAPD_NET, &l2->flag))
		header[1] = 0xff; /* tei 127 */
	header[i++] = UI;
	while ((skb = skb_dequeue(&l2->ui_queue))) {
		memcpy(skb_push(skb, i), header, i);
		enqueue_ui(l2, skb);
	}
}