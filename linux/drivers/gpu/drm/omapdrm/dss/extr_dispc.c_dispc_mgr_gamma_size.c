#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct dispc_gamma_desc {int /*<<< orphan*/  len; } ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_4__ {struct dispc_gamma_desc gamma; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_gamma_table; } ;

/* Variables and functions */
 TYPE_2__* mgr_desc ; 

__attribute__((used)) static u32 dispc_mgr_gamma_size(struct dispc_device *dispc,
				enum omap_channel channel)
{
	const struct dispc_gamma_desc *gdesc = &mgr_desc[channel].gamma;

	if (!dispc->feat->has_gamma_table)
		return 0;

	return gdesc->len;
}