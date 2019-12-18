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
typedef  enum vmw_so_type { ____Placeholder_vmw_so_type } vmw_so_type ;

/* Variables and functions */
#define  SVGA_3D_CMD_DX_DEFINE_BLEND_STATE 139 
#define  SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_STATE 138 
#define  SVGA_3D_CMD_DX_DEFINE_ELEMENTLAYOUT 137 
#define  SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE 136 
#define  SVGA_3D_CMD_DX_DEFINE_SAMPLER_STATE 135 
#define  SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT 134 
#define  SVGA_3D_CMD_DX_DESTROY_BLEND_STATE 133 
#define  SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_STATE 132 
#define  SVGA_3D_CMD_DX_DESTROY_ELEMENTLAYOUT 131 
#define  SVGA_3D_CMD_DX_DESTROY_RASTERIZER_STATE 130 
#define  SVGA_3D_CMD_DX_DESTROY_SAMPLER_STATE 129 
#define  SVGA_3D_CMD_DX_DESTROY_STREAMOUTPUT 128 
 int vmw_so_bs ; 
 int vmw_so_ds ; 
 int vmw_so_el ; 
 int vmw_so_max ; 
 int vmw_so_rs ; 
 int vmw_so_so ; 
 int vmw_so_ss ; 

__attribute__((used)) static inline enum vmw_so_type vmw_so_cmd_to_type(u32 id)
{
	switch (id) {
	case SVGA_3D_CMD_DX_DEFINE_ELEMENTLAYOUT:
	case SVGA_3D_CMD_DX_DESTROY_ELEMENTLAYOUT:
		return vmw_so_el;
	case SVGA_3D_CMD_DX_DEFINE_BLEND_STATE:
	case SVGA_3D_CMD_DX_DESTROY_BLEND_STATE:
		return vmw_so_bs;
	case SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_STATE:
	case SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_STATE:
		return vmw_so_ds;
	case SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE:
	case SVGA_3D_CMD_DX_DESTROY_RASTERIZER_STATE:
		return vmw_so_rs;
	case SVGA_3D_CMD_DX_DEFINE_SAMPLER_STATE:
	case SVGA_3D_CMD_DX_DESTROY_SAMPLER_STATE:
		return vmw_so_ss;
	case SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT:
	case SVGA_3D_CMD_DX_DESTROY_STREAMOUTPUT:
		return vmw_so_so;
	default:
		break;
	}
	return vmw_so_max;
}