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
typedef  int uint32_t ;
struct dce_hwseq {TYPE_1__* masks; } ;
typedef  enum blnd_mode { ____Placeholder_blnd_mode } blnd_mode ;
struct TYPE_2__ {scalar_t__ BLND_ALPHA_MODE; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLNDV_CONTROL ; 
 int /*<<< orphan*/  BLND_ALPHA_MODE ; 
 int /*<<< orphan*/ * BLND_CONTROL ; 
 int /*<<< orphan*/  BLND_FEEDTHROUGH_EN ; 
 int /*<<< orphan*/  BLND_MODE ; 
#define  BLND_MODE_BLENDING 130 
#define  BLND_MODE_CURRENT_PIPE 129 
#define  BLND_MODE_OTHER_PIPE 128 
 int /*<<< orphan*/  BLND_MULTIPLIED_MODE ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void dce_set_blender_mode(struct dce_hwseq *hws,
	unsigned int blnd_inst,
	enum blnd_mode mode)
{
	uint32_t feedthrough = 1;
	uint32_t blnd_mode = 0;
	uint32_t multiplied_mode = 0;
	uint32_t alpha_mode = 2;

	switch (mode) {
	case BLND_MODE_OTHER_PIPE:
		feedthrough = 0;
		blnd_mode = 1;
		alpha_mode = 0;
		break;
	case BLND_MODE_BLENDING:
		feedthrough = 0;
		blnd_mode = 2;
		alpha_mode = 0;
		multiplied_mode = 1;
		break;
	case BLND_MODE_CURRENT_PIPE:
	default:
		if (REG(BLND_CONTROL[blnd_inst]) == REG(BLNDV_CONTROL) ||
				blnd_inst == 0)
			feedthrough = 0;
		break;
	}

	REG_UPDATE(BLND_CONTROL[blnd_inst],
		BLND_MODE, blnd_mode);

	if (hws->masks->BLND_ALPHA_MODE != 0) {
		REG_UPDATE_3(BLND_CONTROL[blnd_inst],
			BLND_FEEDTHROUGH_EN, feedthrough,
			BLND_ALPHA_MODE, alpha_mode,
			BLND_MULTIPLIED_MODE, multiplied_mode);
	}
}