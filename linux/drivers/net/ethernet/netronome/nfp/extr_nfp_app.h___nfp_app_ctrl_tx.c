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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfp_app {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  pf; } ;

/* Variables and functions */
 int __nfp_ctrl_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  priv_to_devlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_devlink_hwmsg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool __nfp_app_ctrl_tx(struct nfp_app *app, struct sk_buff *skb)
{
	trace_devlink_hwmsg(priv_to_devlink(app->pf), false, 0,
			    skb->data, skb->len);

	return __nfp_ctrl_tx(app->ctrl, skb);
}