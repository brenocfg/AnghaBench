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
struct dce_transform {int dummy; } ;
typedef  enum dcp_out_trunc_round_mode { ____Placeholder_dcp_out_trunc_round_mode } dcp_out_trunc_round_mode ;
typedef  enum dcp_out_trunc_round_depth { ____Placeholder_dcp_out_trunc_round_depth } dcp_out_trunc_round_depth ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  DCP_OUT_TRUNC_ROUND_DEPTH_10BIT 136 
#define  DCP_OUT_TRUNC_ROUND_DEPTH_11BIT 135 
#define  DCP_OUT_TRUNC_ROUND_DEPTH_12BIT 134 
#define  DCP_OUT_TRUNC_ROUND_DEPTH_13BIT 133 
#define  DCP_OUT_TRUNC_ROUND_DEPTH_14BIT 132 
#define  DCP_OUT_TRUNC_ROUND_DEPTH_8BIT 131 
#define  DCP_OUT_TRUNC_ROUND_DEPTH_9BIT 130 
#define  DCP_OUT_TRUNC_ROUND_MODE_ROUND 129 
#define  DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE 128 
 int /*<<< orphan*/  OUT_ROUND_CONTROL ; 
 int /*<<< orphan*/  OUT_ROUND_TRUNC_MODE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_round(
	struct dce_transform *xfm_dce,
	enum dcp_out_trunc_round_mode mode,
	enum dcp_out_trunc_round_depth depth)
{
	int depth_bits = 0;
	int mode_bit = 0;

	/*  set up bit depth */
	switch (depth) {
	case DCP_OUT_TRUNC_ROUND_DEPTH_14BIT:
		depth_bits = 6;
		break;
	case DCP_OUT_TRUNC_ROUND_DEPTH_13BIT:
		depth_bits = 7;
		break;
	case DCP_OUT_TRUNC_ROUND_DEPTH_12BIT:
		depth_bits = 0;
		break;
	case DCP_OUT_TRUNC_ROUND_DEPTH_11BIT:
		depth_bits = 1;
		break;
	case DCP_OUT_TRUNC_ROUND_DEPTH_10BIT:
		depth_bits = 2;
		break;
	case DCP_OUT_TRUNC_ROUND_DEPTH_9BIT:
		depth_bits = 3;
		break;
	case DCP_OUT_TRUNC_ROUND_DEPTH_8BIT:
		depth_bits = 4;
		break;
	default:
		depth_bits = 4;
		BREAK_TO_DEBUGGER(); /* Invalid dcp_out_trunc_round_depth */
	}

	/*  set up round or truncate */
	switch (mode) {
	case DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE:
		mode_bit = 0;
		break;
	case DCP_OUT_TRUNC_ROUND_MODE_ROUND:
		mode_bit = 1;
		break;
	default:
		BREAK_TO_DEBUGGER(); /* Invalid dcp_out_trunc_round_mode */
	}

	depth_bits |= mode_bit << 3;

	REG_SET(OUT_ROUND_CONTROL, 0, OUT_ROUND_TRUNC_MODE, depth_bits);
}