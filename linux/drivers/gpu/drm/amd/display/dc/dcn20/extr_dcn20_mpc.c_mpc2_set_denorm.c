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
struct mpc {int dummy; } ;
struct dcn20_mpc {int dummy; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 135 
#define  COLOR_DEPTH_111111 134 
#define  COLOR_DEPTH_121212 133 
#define  COLOR_DEPTH_141414 132 
#define  COLOR_DEPTH_161616 131 
#define  COLOR_DEPTH_666 130 
#define  COLOR_DEPTH_888 129 
#define  COLOR_DEPTH_999 128 
 int /*<<< orphan*/ * DENORM_CONTROL ; 
 int /*<<< orphan*/  MPC_OUT_DENORM_MODE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_mpc* TO_DCN20_MPC (struct mpc*) ; 

void mpc2_set_denorm(
		struct mpc *mpc,
		int opp_id,
		enum dc_color_depth output_depth)
{
	struct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	int denorm_mode = 0;

	switch (output_depth) {
	case COLOR_DEPTH_666:
		denorm_mode = 1;
		break;
	case COLOR_DEPTH_888:
		denorm_mode = 2;
		break;
	case COLOR_DEPTH_999:
		denorm_mode = 3;
		break;
	case COLOR_DEPTH_101010:
		denorm_mode = 4;
		break;
	case COLOR_DEPTH_111111:
		denorm_mode = 5;
		break;
	case COLOR_DEPTH_121212:
		denorm_mode = 6;
		break;
	case COLOR_DEPTH_141414:
	case COLOR_DEPTH_161616:
	default:
		/* not valid used case! */
		break;
	}

	REG_UPDATE(DENORM_CONTROL[opp_id],
			MPC_OUT_DENORM_MODE, denorm_mode);
}