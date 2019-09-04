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
struct vpbe_device {int current_sd_index; struct vpbe_config* cfg; } ;
struct encoder_config_info {int dummy; } ;
struct vpbe_config {struct encoder_config_info* ext_encoders; struct encoder_config_info venc; } ;

/* Variables and functions */

__attribute__((used)) static struct encoder_config_info*
vpbe_current_encoder_info(struct vpbe_device *vpbe_dev)
{
	struct vpbe_config *cfg = vpbe_dev->cfg;
	int index = vpbe_dev->current_sd_index;

	return ((index == 0) ? &cfg->venc :
				&cfg->ext_encoders[index-1]);
}