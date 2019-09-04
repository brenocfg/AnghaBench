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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_BLANK_DATA_DOUBLE_BUFFER_EN ; 
 int /*<<< orphan*/  OTG_DOUBLE_BUFFER_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void optc1_set_blank_data_double_buffer(struct timing_generator *optc, bool enable)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	uint32_t blank_data_double_buffer_enable = enable ? 1 : 0;

	REG_UPDATE(OTG_DOUBLE_BUFFER_CONTROL,
			OTG_BLANK_DATA_DOUBLE_BUFFER_EN, blank_data_double_buffer_enable);
}