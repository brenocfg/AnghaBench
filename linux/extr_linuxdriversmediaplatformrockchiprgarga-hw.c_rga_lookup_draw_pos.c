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
typedef  size_t u32 ;
struct rga_addr_offset {int dummy; } ;
struct rga_corners_addr_offset {struct rga_addr_offset right_bottom; struct rga_addr_offset right_top; struct rga_addr_offset left_bottom; struct rga_addr_offset left_top; } ;
typedef  enum e_rga_start_pos { ____Placeholder_e_rga_start_pos } e_rga_start_pos ;

/* Variables and functions */
#define  LB 131 
#define  LT 130 
#define  RB 129 
#define  RT 128 

__attribute__((used)) static struct rga_addr_offset *rga_lookup_draw_pos(struct
		rga_corners_addr_offset
		* offsets, u32 rotate_mode,
		u32 mirr_mode)
{
	static enum e_rga_start_pos rot_mir_point_matrix[4][4] = {
		{
			LT, RT, LB, RB,
		},
		{
			RT, LT, RB, LB,
		},
		{
			RB, LB, RT, LT,
		},
		{
			LB, RB, LT, RT,
		},
	};

	if (!offsets)
		return NULL;

	switch (rot_mir_point_matrix[rotate_mode][mirr_mode]) {
	case LT:
		return &offsets->left_top;
	case LB:
		return &offsets->left_bottom;
	case RT:
		return &offsets->right_top;
	case RB:
		return &offsets->right_bottom;
	}

	return NULL;
}