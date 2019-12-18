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
struct w1_netlink_msg {int dummy; } ;
struct w1_master {int dummy; } ;

/* Variables and functions */

void w1_netlink_send(struct w1_master *dev, struct w1_netlink_msg *cn)
{
}