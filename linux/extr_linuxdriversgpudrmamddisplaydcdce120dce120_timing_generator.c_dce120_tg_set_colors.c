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
struct tg_color {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce120_tg_program_blank_color (struct timing_generator*,struct tg_color const*) ; 
 int /*<<< orphan*/  dce120_tg_set_overscan_color (struct timing_generator*,struct tg_color const*) ; 

void dce120_tg_set_colors(struct timing_generator *tg,
	const struct tg_color *blank_color,
	const struct tg_color *overscan_color)
{
	if (blank_color != NULL)
		dce120_tg_program_blank_color(tg, blank_color);

	if (overscan_color != NULL)
		dce120_tg_set_overscan_color(tg, overscan_color);
}