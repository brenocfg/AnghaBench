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
struct fpga_image_info {int /*<<< orphan*/  disable_timeout_us; int /*<<< orphan*/  enable_timeout_us; } ;
struct fpga_bridge {struct altera_freeze_br_data* priv; struct fpga_image_info* info; } ;
struct altera_freeze_br_data {int enable; } ;

/* Variables and functions */
 int altera_freeze_br_do_freeze (struct altera_freeze_br_data*,int /*<<< orphan*/ ) ; 
 int altera_freeze_br_do_unfreeze (struct altera_freeze_br_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_freeze_br_enable_set(struct fpga_bridge *bridge,
				       bool enable)
{
	struct altera_freeze_br_data *priv = bridge->priv;
	struct fpga_image_info *info = bridge->info;
	u32 timeout = 0;
	int ret;

	if (enable) {
		if (info)
			timeout = info->enable_timeout_us;

		ret = altera_freeze_br_do_unfreeze(bridge->priv, timeout);
	} else {
		if (info)
			timeout = info->disable_timeout_us;

		ret = altera_freeze_br_do_freeze(bridge->priv, timeout);
	}

	if (!ret)
		priv->enable = enable;

	return ret;
}