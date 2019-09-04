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
typedef  scalar_t__ uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_BLANK_CONTROL ; 
 int /*<<< orphan*/  OTG_BLANK_DATA_EN ; 
 int /*<<< orphan*/  OTG_BLANK_DE_MODE ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT2_CONTROL ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT2_INT_ENABLE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optc1_set_blank_data_double_buffer (struct timing_generator*,int) ; 

__attribute__((used)) static void optc1_unblank_crtc(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);
	uint32_t vertical_interrupt_enable = 0;

	REG_GET(OTG_VERTICAL_INTERRUPT2_CONTROL,
			OTG_VERTICAL_INTERRUPT2_INT_ENABLE, &vertical_interrupt_enable);

	/* temporary work around for vertical interrupt, once vertical interrupt enabled,
	 * this check will be removed.
	 */
	if (vertical_interrupt_enable)
		optc1_set_blank_data_double_buffer(optc, true);

	REG_UPDATE_2(OTG_BLANK_CONTROL,
			OTG_BLANK_DATA_EN, 0,
			OTG_BLANK_DE_MODE, 0);
}