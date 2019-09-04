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
typedef  int u32 ;
typedef  enum vmw_view_type { ____Placeholder_vmw_view_type } vmw_view_type ;

/* Variables and functions */
 int SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW ; 
 int vmw_view_max ; 

__attribute__((used)) static inline enum vmw_view_type vmw_view_cmd_to_type(u32 id)
{
	u32 tmp = (id - SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW) / 2;

	if (tmp > (u32)vmw_view_max)
		return vmw_view_max;

	return (enum vmw_view_type) tmp;
}