#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct dispc_gamma_desc {int /*<<< orphan*/  len; } ;
struct dispc_device {int /*<<< orphan*/ ** gamma_table; TYPE_1__* pdev; TYPE_2__* feat; } ;
struct TYPE_6__ {struct dispc_gamma_desc gamma; } ;
struct TYPE_5__ {int /*<<< orphan*/  has_gamma_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FEAT_MGR_LCD2 ; 
 int /*<<< orphan*/  FEAT_MGR_LCD3 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OMAP_DSS_CHANNEL_LCD2 ; 
 int OMAP_DSS_CHANNEL_LCD3 ; 
 int /*<<< orphan*/ * devm_kmalloc_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_gamma (struct dispc_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* mgr_desc ; 

__attribute__((used)) static int dispc_init_gamma_tables(struct dispc_device *dispc)
{
	int channel;

	if (!dispc->feat->has_gamma_table)
		return 0;

	for (channel = 0; channel < ARRAY_SIZE(dispc->gamma_table); channel++) {
		const struct dispc_gamma_desc *gdesc = &mgr_desc[channel].gamma;
		u32 *gt;

		if (channel == OMAP_DSS_CHANNEL_LCD2 &&
		    !dispc_has_feature(dispc, FEAT_MGR_LCD2))
			continue;

		if (channel == OMAP_DSS_CHANNEL_LCD3 &&
		    !dispc_has_feature(dispc, FEAT_MGR_LCD3))
			continue;

		gt = devm_kmalloc_array(&dispc->pdev->dev, gdesc->len,
					sizeof(u32), GFP_KERNEL);
		if (!gt)
			return -ENOMEM;

		dispc->gamma_table[channel] = gt;

		dispc_mgr_set_gamma(dispc, channel, NULL, 0);
	}
	return 0;
}