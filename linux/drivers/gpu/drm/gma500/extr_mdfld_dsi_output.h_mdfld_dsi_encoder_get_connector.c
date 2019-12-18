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
struct mdfld_dsi_encoder {int dummy; } ;
struct mdfld_dsi_connector {int dummy; } ;
struct mdfld_dsi_config {struct mdfld_dsi_connector* connector; } ;

/* Variables and functions */
 struct mdfld_dsi_config* mdfld_dsi_encoder_get_config (struct mdfld_dsi_encoder*) ; 

__attribute__((used)) static inline struct mdfld_dsi_connector *
	mdfld_dsi_encoder_get_connector(struct mdfld_dsi_encoder *encoder)
{
	struct mdfld_dsi_config *config;

	if (!encoder)
		return NULL;

	config = mdfld_dsi_encoder_get_config(encoder);
	if (!config)
		return NULL;

	return config->connector;
}