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
typedef  int uint32_t ;
struct hubbub {int dummy; } ;
struct dcn20_hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_ENABLE ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_REFDIV ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 struct dcn20_hubbub* TO_DCN20_HUBBUB (struct hubbub*) ; 

void hubbub2_get_dchub_ref_freq(struct hubbub *hubbub,
		unsigned int dccg_ref_freq_inKhz,
		unsigned int *dchub_ref_freq_inKhz)
{
	struct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uint32_t ref_div = 0;
	uint32_t ref_en = 0;

	REG_GET_2(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_REFDIV, &ref_div,
			DCHUBBUB_GLOBAL_TIMER_ENABLE, &ref_en);

	if (ref_en) {
		if (ref_div == 2)
			*dchub_ref_freq_inKhz = dccg_ref_freq_inKhz / 2;
		else
			*dchub_ref_freq_inKhz = dccg_ref_freq_inKhz;

		// DC hub reference frequency must be around 50Mhz, otherwise there may be
		// overflow/underflow issues when doing HUBBUB programming
		if (*dchub_ref_freq_inKhz < 40000 || *dchub_ref_freq_inKhz > 60000)
			ASSERT_CRITICAL(false);

		return;
	} else {
		*dchub_ref_freq_inKhz = dccg_ref_freq_inKhz;

		// HUBBUB global timer must be enabled.
		ASSERT_CRITICAL(false);
		return;
	}
}