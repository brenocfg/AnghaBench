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
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  genlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void drbd_adm_send_reply(struct sk_buff *skb, struct genl_info *info)
{
	genlmsg_end(skb, genlmsg_data(nlmsg_data(nlmsg_hdr(skb))));
	if (genlmsg_reply(skb, info))
		pr_err("error sending genl reply\n");
}