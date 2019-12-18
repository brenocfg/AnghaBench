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
struct mdfld_dsi_connector {void* pkg_sender; } ;
struct mdfld_dsi_config {struct mdfld_dsi_connector* connector; } ;

/* Variables and functions */

__attribute__((used)) static inline void *mdfld_dsi_get_pkg_sender(struct mdfld_dsi_config *config)
{
	struct mdfld_dsi_connector *dsi_connector;

	if (!config)
		return NULL;

	dsi_connector = config->connector;

	if (!dsi_connector)
		return NULL;

	return dsi_connector->pkg_sender;
}