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
struct netlink_skb_parms {int dummy; } ;
struct dm_ulog_request {int dummy; } ;
struct cn_msg {int len; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DMERR (char*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pkg (struct cn_msg*,struct dm_ulog_request*) ; 
 int /*<<< orphan*/  receiving_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cn_ulog_callback(struct cn_msg *msg, struct netlink_skb_parms *nsp)
{
	struct dm_ulog_request *tfr = (struct dm_ulog_request *)(msg + 1);

	if (!capable(CAP_SYS_ADMIN))
		return;

	spin_lock(&receiving_list_lock);
	if (msg->len == 0)
		fill_pkg(msg, NULL);
	else if (msg->len < sizeof(*tfr))
		DMERR("Incomplete message received (expected %u, got %u): [%u]",
		      (unsigned)sizeof(*tfr), msg->len, msg->seq);
	else
		fill_pkg(NULL, tfr);
	spin_unlock(&receiving_list_lock);
}