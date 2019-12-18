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
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT0_LINE_END ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT0_LINE_START ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT0_POSITION ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc1_setup_vertical_interrupt0(
		struct timing_generator *optc,
		uint32_t start_line,
		uint32_t end_line)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_2(OTG_VERTICAL_INTERRUPT0_POSITION, 0,
			OTG_VERTICAL_INTERRUPT0_LINE_START, start_line,
			OTG_VERTICAL_INTERRUPT0_LINE_END, end_line);
}