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
struct nfp_app {TYPE_1__* type; } ;
struct TYPE_2__ {scalar_t__ ctrl_msg_rx_raw; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nfp_app_ctrl_uses_data_vnics(struct nfp_app *app)
{
	return app && app->type->ctrl_msg_rx_raw;
}