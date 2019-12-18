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
struct txfcb {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_FCB_LEN ; 
 int /*<<< orphan*/  memset (struct txfcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct txfcb* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct txfcb *gfar_add_fcb(struct sk_buff *skb)
{
	struct txfcb *fcb = skb_push(skb, GMAC_FCB_LEN);

	memset(fcb, 0, GMAC_FCB_LEN);

	return fcb;
}