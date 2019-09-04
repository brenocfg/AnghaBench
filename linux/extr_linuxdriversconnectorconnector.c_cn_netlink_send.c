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
typedef  int /*<<< orphan*/  u32 ;
struct cn_msg {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int cn_netlink_send_mult (struct cn_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cn_netlink_send(struct cn_msg *msg, u32 portid, u32 __group,
	gfp_t gfp_mask)
{
	return cn_netlink_send_mult(msg, msg->len, portid, __group, gfp_mask);
}