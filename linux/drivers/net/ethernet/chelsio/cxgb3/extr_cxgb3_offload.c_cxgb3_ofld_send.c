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
struct t3cdev {int (* send ) (struct t3cdev*,struct sk_buff*) ;} ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int stub1 (struct t3cdev*,struct sk_buff*) ; 

int cxgb3_ofld_send(struct t3cdev *dev, struct sk_buff *skb)
{
	int r;

	local_bh_disable();
	r = dev->send(dev, skb);
	local_bh_enable();
	return r;
}