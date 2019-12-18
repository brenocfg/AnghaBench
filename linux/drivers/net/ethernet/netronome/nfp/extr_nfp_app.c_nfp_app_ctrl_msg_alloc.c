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
struct nfp_app {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_app_ctrl_has_meta (struct nfp_app*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

struct sk_buff *
nfp_app_ctrl_msg_alloc(struct nfp_app *app, unsigned int size, gfp_t priority)
{
	struct sk_buff *skb;

	if (nfp_app_ctrl_has_meta(app))
		size += 8;

	skb = alloc_skb(size, priority);
	if (!skb)
		return NULL;

	if (nfp_app_ctrl_has_meta(app))
		skb_reserve(skb, 8);

	return skb;
}