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
struct sk_buff {scalar_t__ cb; } ;
struct c4iw_ep {int dummy; } ;
struct c4iw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_ep_resources (struct c4iw_ep*) ; 

__attribute__((used)) static int _put_ep_safe(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct c4iw_ep *ep;

	ep = *((struct c4iw_ep **)(skb->cb + 2 * sizeof(void *)));
	release_ep_resources(ep);
	return 0;
}