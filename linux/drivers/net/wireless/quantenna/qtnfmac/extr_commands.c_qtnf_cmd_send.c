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
struct qtnf_bus {int dummy; } ;
struct qlink_resp {int dummy; } ;

/* Variables and functions */
 int qtnf_cmd_send_with_reply (struct qtnf_bus*,struct sk_buff*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int qtnf_cmd_send(struct qtnf_bus *bus, struct sk_buff *cmd_skb)
{
	return qtnf_cmd_send_with_reply(bus, cmd_skb, NULL,
					sizeof(struct qlink_resp), NULL);
}