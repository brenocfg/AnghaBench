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
struct g2d_data {int /*<<< orphan*/  dev; } ;
typedef  enum g2d_reg_type { ____Placeholder_g2d_reg_type } g2d_reg_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
#define  G2D_DST_BASE_ADDR 141 
#define  G2D_DST_COLOR_MODE 140 
#define  G2D_DST_LEFT_TOP 139 
#define  G2D_DST_PLANE2_BASE_ADDR 138 
#define  G2D_DST_RIGHT_BOTTOM 137 
#define  G2D_DST_STRIDE 136 
#define  G2D_MSK_BASE_ADDR 135 
#define  G2D_PAT_BASE_ADDR 134 
#define  G2D_SRC_BASE_ADDR 133 
#define  G2D_SRC_COLOR_MODE 132 
#define  G2D_SRC_LEFT_TOP 131 
#define  G2D_SRC_PLANE2_BASE_ADDR 130 
#define  G2D_SRC_RIGHT_BOTTOM 129 
#define  G2D_SRC_STRIDE 128 
 int REG_TYPE_DST ; 
 int REG_TYPE_DST_PLANE2 ; 
 int REG_TYPE_MSK ; 
 int REG_TYPE_NONE ; 
 int REG_TYPE_PAT ; 
 int REG_TYPE_SRC ; 
 int REG_TYPE_SRC_PLANE2 ; 

__attribute__((used)) static enum g2d_reg_type g2d_get_reg_type(struct g2d_data *g2d, int reg_offset)
{
	enum g2d_reg_type reg_type;

	switch (reg_offset) {
	case G2D_SRC_BASE_ADDR:
	case G2D_SRC_STRIDE:
	case G2D_SRC_COLOR_MODE:
	case G2D_SRC_LEFT_TOP:
	case G2D_SRC_RIGHT_BOTTOM:
		reg_type = REG_TYPE_SRC;
		break;
	case G2D_SRC_PLANE2_BASE_ADDR:
		reg_type = REG_TYPE_SRC_PLANE2;
		break;
	case G2D_DST_BASE_ADDR:
	case G2D_DST_STRIDE:
	case G2D_DST_COLOR_MODE:
	case G2D_DST_LEFT_TOP:
	case G2D_DST_RIGHT_BOTTOM:
		reg_type = REG_TYPE_DST;
		break;
	case G2D_DST_PLANE2_BASE_ADDR:
		reg_type = REG_TYPE_DST_PLANE2;
		break;
	case G2D_PAT_BASE_ADDR:
		reg_type = REG_TYPE_PAT;
		break;
	case G2D_MSK_BASE_ADDR:
		reg_type = REG_TYPE_MSK;
		break;
	default:
		reg_type = REG_TYPE_NONE;
		DRM_DEV_ERROR(g2d->dev, "Unknown register offset![%d]\n",
			      reg_offset);
		break;
	}

	return reg_type;
}