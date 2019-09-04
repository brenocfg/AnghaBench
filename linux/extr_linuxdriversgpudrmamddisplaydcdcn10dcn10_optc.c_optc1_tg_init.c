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
struct timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  optc1_clear_optc_underflow (struct timing_generator*) ; 
 int /*<<< orphan*/  optc1_set_blank_data_double_buffer (struct timing_generator*,int) ; 

void optc1_tg_init(struct timing_generator *optc)
{
	optc1_set_blank_data_double_buffer(optc, true);
	optc1_clear_optc_underflow(optc);
}