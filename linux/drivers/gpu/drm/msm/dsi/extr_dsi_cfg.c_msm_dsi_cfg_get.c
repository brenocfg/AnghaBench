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
typedef  scalar_t__ u32 ;
struct msm_dsi_cfg_handler {scalar_t__ major; scalar_t__ minor; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct msm_dsi_cfg_handler*) ; 
 struct msm_dsi_cfg_handler* dsi_cfg_handlers ; 

const struct msm_dsi_cfg_handler *msm_dsi_cfg_get(u32 major, u32 minor)
{
	const struct msm_dsi_cfg_handler *cfg_hnd = NULL;
	int i;

	for (i = ARRAY_SIZE(dsi_cfg_handlers) - 1; i >= 0; i--) {
		if ((dsi_cfg_handlers[i].major == major) &&
			(dsi_cfg_handlers[i].minor == minor)) {
			cfg_hnd = &dsi_cfg_handlers[i];
			break;
		}
	}

	return cfg_hnd;
}