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
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ qxl_add_common_modes (struct drm_connector*,unsigned int,unsigned int) ; 
 int qxl_add_monitors_config_modes (struct drm_connector*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int qxl_conn_get_modes(struct drm_connector *connector)
{
	unsigned pwidth = 1024;
	unsigned pheight = 768;
	int ret = 0;

	ret = qxl_add_monitors_config_modes(connector, &pwidth, &pheight);
	if (ret < 0)
		return ret;
	ret += qxl_add_common_modes(connector, pwidth, pheight);
	return ret;
}