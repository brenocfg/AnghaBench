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
typedef  int u16 ;
struct wsm_edca_params {scalar_t__* uapsd_enable; } ;
struct TYPE_2__ {scalar_t__ auto_trigger_step; scalar_t__ max_auto_trigger_interval; scalar_t__ min_auto_trigger_interval; int /*<<< orphan*/  uapsd_flags; } ;
struct cw1200_common {TYPE_1__ uapsd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int wsm_set_uapsd_info (struct cw1200_common*,TYPE_1__*) ; 

int cw1200_set_uapsd_param(struct cw1200_common *priv,
			   const struct wsm_edca_params *arg)
{
	int ret;
	u16 uapsd_flags = 0;

	/* Here's the mapping AC [queue, bit]
	 *  VO [0,3], VI [1, 2], BE [2, 1], BK [3, 0]
	 */

	if (arg->uapsd_enable[0])
		uapsd_flags |= 1 << 3;

	if (arg->uapsd_enable[1])
		uapsd_flags |= 1 << 2;

	if (arg->uapsd_enable[2])
		uapsd_flags |= 1 << 1;

	if (arg->uapsd_enable[3])
		uapsd_flags |= 1;

	/* Currently pseudo U-APSD operation is not supported, so setting
	 * MinAutoTriggerInterval, MaxAutoTriggerInterval and
	 * AutoTriggerStep to 0
	 */

	priv->uapsd_info.uapsd_flags = cpu_to_le16(uapsd_flags);
	priv->uapsd_info.min_auto_trigger_interval = 0;
	priv->uapsd_info.max_auto_trigger_interval = 0;
	priv->uapsd_info.auto_trigger_step = 0;

	ret = wsm_set_uapsd_info(priv, &priv->uapsd_info);
	return ret;
}