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
struct dce110_opp {TYPE_1__* opp_mask; } ;
struct clamping_and_pixel_encoding_params {scalar_t__ pixel_encoding; } ;
struct TYPE_2__ {scalar_t__ FMT_CBCR_BIT_REDUCTION_BYPASS; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_CBCR_BIT_REDUCTION_BYPASS ; 
 int /*<<< orphan*/  FMT_CONTROL ; 
 int /*<<< orphan*/  FMT_PIXEL_ENCODING ; 
 int /*<<< orphan*/  FMT_SUBSAMPLING_MODE ; 
 int /*<<< orphan*/  FMT_SUBSAMPLING_ORDER ; 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_pixel_encoding(
	struct dce110_opp *opp110,
	const struct clamping_and_pixel_encoding_params *params)
{
	if (opp110->opp_mask->FMT_CBCR_BIT_REDUCTION_BYPASS)
		REG_UPDATE_3(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 0,
				FMT_SUBSAMPLING_MODE, 0,
				FMT_CBCR_BIT_REDUCTION_BYPASS, 0);
	else
		REG_UPDATE_2(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 0,
				FMT_SUBSAMPLING_MODE, 0);

	if (params->pixel_encoding == PIXEL_ENCODING_YCBCR422) {
		REG_UPDATE_2(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 1,
				FMT_SUBSAMPLING_ORDER, 0);
	}
	if (params->pixel_encoding == PIXEL_ENCODING_YCBCR420) {
		REG_UPDATE_3(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 2,
				FMT_SUBSAMPLING_MODE, 2,
				FMT_CBCR_BIT_REDUCTION_BYPASS, 1);
	}

}