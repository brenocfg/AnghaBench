#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dce110_opp {int dummy; } ;
struct TYPE_2__ {int TRUNCATE_DEPTH; scalar_t__ TRUNCATE_ENABLED; int /*<<< orphan*/  TRUNCATE_MODE; } ;
struct bit_depth_reduction_params {scalar_t__ pixel_encoding; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_BIT_DEPTH_CONTROL ; 
 int /*<<< orphan*/  FMT_TRUNCATE_DEPTH ; 
 int /*<<< orphan*/  FMT_TRUNCATE_EN ; 
 int /*<<< orphan*/  FMT_TRUNCATE_MODE ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_truncation(
		struct dce110_opp *opp110,
		const struct bit_depth_reduction_params *params)
{
	/*Disable truncation*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
			FMT_TRUNCATE_EN, 0,
			FMT_TRUNCATE_DEPTH, 0,
			FMT_TRUNCATE_MODE, 0);


	if (params->pixel_encoding == PIXEL_ENCODING_YCBCR422) {
		/*  8bpc trunc on YCbCr422*/
		if (params->flags.TRUNCATE_DEPTH == 1)
			REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
					FMT_TRUNCATE_EN, 1,
					FMT_TRUNCATE_DEPTH, 1,
					FMT_TRUNCATE_MODE, 0);
		else if (params->flags.TRUNCATE_DEPTH == 2)
			/*  10bpc trunc on YCbCr422*/
			REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
					FMT_TRUNCATE_EN, 1,
					FMT_TRUNCATE_DEPTH, 2,
					FMT_TRUNCATE_MODE, 0);
		return;
	}
	/* on other format-to do */
	if (params->flags.TRUNCATE_ENABLED == 0)
		return;
	/*Set truncation depth and Enable truncation*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
				FMT_TRUNCATE_EN, 1,
				FMT_TRUNCATE_DEPTH,
				params->flags.TRUNCATE_DEPTH,
				FMT_TRUNCATE_MODE,
				params->flags.TRUNCATE_MODE);
}