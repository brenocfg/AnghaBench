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
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_remain_on_chan {int dummy; } ;
struct TYPE_2__ {struct host_cmd_ds_remain_on_chan roc_cfg; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct host_cmd_ds_remain_on_chan*,struct host_cmd_ds_remain_on_chan*,int) ; 

__attribute__((used)) static int
mwifiex_ret_remain_on_chan(struct mwifiex_private *priv,
			   struct host_cmd_ds_command *resp,
			   struct host_cmd_ds_remain_on_chan *roc_cfg)
{
	struct host_cmd_ds_remain_on_chan *resp_cfg = &resp->params.roc_cfg;

	if (roc_cfg)
		memcpy(roc_cfg, resp_cfg, sizeof(*roc_cfg));

	return 0;
}