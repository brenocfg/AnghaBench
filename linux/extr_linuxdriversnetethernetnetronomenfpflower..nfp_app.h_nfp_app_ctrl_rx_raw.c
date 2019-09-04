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
struct nfp_app {TYPE_1__* type; int /*<<< orphan*/  pf; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ctrl_msg_rx_raw ) (struct nfp_app*,void const*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  priv_to_devlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfp_app*,void const*,unsigned int) ; 
 int /*<<< orphan*/  trace_devlink_hwmsg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void const*,unsigned int) ; 

__attribute__((used)) static inline void
nfp_app_ctrl_rx_raw(struct nfp_app *app, const void *data, unsigned int len)
{
	if (!app || !app->type->ctrl_msg_rx_raw)
		return;

	trace_devlink_hwmsg(priv_to_devlink(app->pf), true, 0, data, len);
	app->type->ctrl_msg_rx_raw(app, data, len);
}