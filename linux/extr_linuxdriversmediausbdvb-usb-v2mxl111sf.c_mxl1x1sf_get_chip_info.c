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
typedef  int u8 ;
struct mxl111sf_state {int chip_id; int chip_ver; int /*<<< orphan*/  chip_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ID_REG ; 
 int /*<<< orphan*/  MXL111SF_V6 ; 
 int /*<<< orphan*/  MXL111SF_V8_100 ; 
 int /*<<< orphan*/  MXL111SF_V8_200 ; 
 int /*<<< orphan*/  TOP_CHIP_REV_ID_REG ; 
 int mxl111sf_read_reg (struct mxl111sf_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  pr_info (char*,char*,char*,int) ; 

__attribute__((used)) static int mxl1x1sf_get_chip_info(struct mxl111sf_state *state)
{
	int ret;
	u8 id, ver;
	char *mxl_chip, *mxl_rev;

	if ((state->chip_id) && (state->chip_ver))
		return 0;

	ret = mxl111sf_read_reg(state, CHIP_ID_REG, &id);
	if (mxl_fail(ret))
		goto fail;
	state->chip_id = id;

	ret = mxl111sf_read_reg(state, TOP_CHIP_REV_ID_REG, &ver);
	if (mxl_fail(ret))
		goto fail;
	state->chip_ver = ver;

	switch (id) {
	case 0x61:
		mxl_chip = "MxL101SF";
		break;
	case 0x63:
		mxl_chip = "MxL111SF";
		break;
	default:
		mxl_chip = "UNKNOWN MxL1X1";
		break;
	}
	switch (ver) {
	case 0x36:
		state->chip_rev = MXL111SF_V6;
		mxl_rev = "v6";
		break;
	case 0x08:
		state->chip_rev = MXL111SF_V8_100;
		mxl_rev = "v8_100";
		break;
	case 0x18:
		state->chip_rev = MXL111SF_V8_200;
		mxl_rev = "v8_200";
		break;
	default:
		state->chip_rev = 0;
		mxl_rev = "UNKNOWN REVISION";
		break;
	}
	pr_info("%s detected, %s (0x%x)", mxl_chip, mxl_rev, ver);
fail:
	return ret;
}