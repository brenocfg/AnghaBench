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
struct netlink_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nldev_get_dumpit ; 
 int ib_enum_all_devs (int /*<<< orphan*/ ,struct sk_buff*,struct netlink_callback*) ; 

__attribute__((used)) static int nldev_get_dumpit(struct sk_buff *skb, struct netlink_callback *cb)
{
	/*
	 * There is no need to take lock, because
	 * we are relying on ib_core's locking.
	 */
	return ib_enum_all_devs(_nldev_get_dumpit, skb, cb);
}