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
typedef  scalar_t__ u16 ;
struct sun6i_dsi {int dummy; } ;
struct drm_display_mode {int hdisplay; } ;

/* Variables and functions */
 int SUN6I_DSI_TCON_DIV ; 

__attribute__((used)) static u16 sun6i_dsi_get_drq_edge0(struct sun6i_dsi *dsi,
				   struct drm_display_mode *mode,
				   u16 line_num, u16 edge1)
{
	u16 edge0 = edge1;

	edge0 += (mode->hdisplay + 40) * SUN6I_DSI_TCON_DIV / 8;

	if (edge0 > line_num)
		return edge0 - line_num;

	return 1;
}