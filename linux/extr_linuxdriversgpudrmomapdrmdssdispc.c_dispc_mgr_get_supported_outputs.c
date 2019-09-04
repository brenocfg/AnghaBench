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
struct dispc_device {int /*<<< orphan*/  dss; } ;
typedef  enum omap_dss_output_id { ____Placeholder_omap_dss_output_id } omap_dss_output_id ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int dss_get_supported_outputs (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum omap_dss_output_id
dispc_mgr_get_supported_outputs(struct dispc_device *dispc,
				enum omap_channel channel)
{
	return dss_get_supported_outputs(dispc->dss, channel);
}