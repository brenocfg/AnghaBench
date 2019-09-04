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
struct mdfld_dsi_connector {scalar_t__ private; } ;
struct mdfld_dsi_config {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mdfld_dsi_config *
	mdfld_dsi_get_config(struct mdfld_dsi_connector *connector)
{
	if (!connector)
		return NULL;
	return (struct mdfld_dsi_config *)connector->private;
}