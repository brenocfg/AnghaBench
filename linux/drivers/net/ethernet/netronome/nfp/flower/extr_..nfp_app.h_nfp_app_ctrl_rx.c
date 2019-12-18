#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfp_app {TYPE_1__* type; int /*<<< orphan*/  pf; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ctrl_msg_rx ) (struct nfp_app*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  priv_to_devlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfp_app*,struct sk_buff*) ; 
 int /*<<< orphan*/  trace_devlink_hwmsg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nfp_app_ctrl_rx(struct nfp_app *app, struct sk_buff *skb)
{
	trace_devlink_hwmsg(priv_to_devlink(app->pf), true, 0,
			    skb->data, skb->len);

	app->type->ctrl_msg_rx(app, skb);
}